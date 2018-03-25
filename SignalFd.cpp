//
// Created by xiaotie on 18-3-25.
//

#include "SignalFd.h"

const static int MAX_EVENTS = 1;

SignalFd::SignalFd(int signal) : _stopSignal(signal), _signalInfo() {
    ::sigset_t mask{};
    ::sigemptyset(&mask);
    ::sigaddset(&mask, signal);
    if (::sigprocmask(SIG_BLOCK, &mask, nullptr) < 0) {
        perror("sigprocmask err.");
        ::exit(-1);
    }

    _fdSignal = ::signalfd(-1, &mask, 0);
    if (_fdSignal < 0) {
        perror("signalfd err.");
        ::exit(0);
    }

    _fdEpoll = ::epoll_create(MAX_EVENTS);
    ::epoll_event events[MAX_EVENTS];
    ::epoll_event ev{};
    ev.data.fd = _fdSignal;
    ev.events = EPOLLIN;
    ::epoll_ctl(_fdEpoll, EPOLL_CTL_ADD, _fdSignal, &ev);

    _thrd = std::thread([&]() {
        while (true) {
            printf("Waiting For Stop Signal\n");
            ::epoll_wait(_fdEpoll, events, MAX_EVENTS, -1);
            ssize_t len = read(_fdSignal, &_signalInfo, sizeof(_signalInfo));

            if (_signalInfo.ssi_signo == SIGINT) {
                if (SIGINT == _stopSignal) {
                    printf("get SIGINT And Stop.\n");
                    return;
                } else {
                    printf("get SIGINT.\n");
                }
            }
            if (_signalInfo.ssi_signo == SIGQUIT) {
                if (SIGQUIT == _stopSignal) {
                    printf("get SIGQUIT And Stop.\n");
                    return;
                } else {
                    printf("get SIGQUIT.\n");
                }
            }
        }
    });
}

SignalFd::~SignalFd() {
    ::close(_fdEpoll);
    ::close(_fdSignal);
}

void SignalFd::sendSignal(int signal) {
    pthread_t threadId = _thrd.native_handle();
    pthread_kill(threadId, signal);
}