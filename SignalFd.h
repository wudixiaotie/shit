//
// Created by xiaotie on 18-3-25.
//

#ifndef SHIT_SIGNALFD_H
#define SHIT_SIGNALFD_H

#include <pthread.h>
#include <sys/epoll.h>
#include <sys/signal.h>
#include <sys/signalfd.h>
#include <cstdio>
#include <cstdlib>
#include <zconf.h>
#include <thread>

class SignalFd {
private:
    int _stopSignal;
    int _fdEpoll;
    int _fdSignal;
    ::signalfd_siginfo _signalInfo;
    std::thread _thrd;
public:
    explicit SignalFd(int signal);

    ~SignalFd();

    void sendSignal(int signal);
};


#endif //SHIT_SIGNALFD_H
