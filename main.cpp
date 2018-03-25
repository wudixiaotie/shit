/*
#include <iostream>
#include <sys/epoll.h>
#include <zconf.h>
#include <cstring>

const static int MAX_EVENTS = 1;
const static int BUF_SIZE = 100;

int main() {
    int fdEpoll = ::epoll_create(MAX_EVENTS);
    ::epoll_event events[MAX_EVENTS];
    ::epoll_event ev{};
    ev.data.fd = STDIN_FILENO;
    ev.events = EPOLLIN;
    ::epoll_ctl(fdEpoll, EPOLL_CTL_ADD, STDIN_FILENO, &ev);
    while (true) {
        ::epoll_wait(fdEpoll, events, MAX_EVENTS, -1);
        char buf[BUF_SIZE];
        ssize_t len = read(STDIN_FILENO, buf, BUF_SIZE);
        buf[len] = '\0';
        if (::strcmp(buf, "stop\n") == 0) {
            break;
        } else {
            printf("input: %s", buf);
        }
    }
    return 0;
}*/

#include <bits/signum.h>
#include "SignalFd.h"

/*
#include <sys/signal.h>
#include <sys/signalfd.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include "SignalFd.h"

int main() {
    sigset_t mask{};
    int sigfd;
    signalfd_siginfo ssinfo{};
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &mask, nullptr) < 0) {
        perror("sigprocmask err.");
        ::exit(-1);
    }
    if ((sigfd = signalfd(-1, &mask, 0)) < 0) {
        perror("signalfd err.");
        exit(0);
    }
    while (true) {
        ssize_t len = read(sigfd, &ssinfo, sizeof(ssinfo));
        if (len < 0) {
            perror("read err.");
            exit(-1);
        }
        if (ssinfo.ssi_signo == SIGINT) {
            printf("get SIGINT./n");
            continue;
        }
        if (ssinfo.ssi_signo == SIGQUIT) {
            printf("get SIGUIT./n");
            break;
        }
    }
    return 0;
}*/


int main() {
    SignalFd signalInt(SIGINT);
    SignalFd signalQuit(SIGQUIT);
    sleep(2);
    signalInt.sendSignal(SIGQUIT);
    signalQuit.sendSignal(SIGINT);
}