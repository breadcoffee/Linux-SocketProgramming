# Linux-SocketProgramming-2024
부경대 2024 IoT 개발자 과정 리눅스 소켓프로그래밍 학습 리포지토리

## 1일차

- TCP(Transmission Control Protocol, TCP)
    - 전송방식(일방향 UDP, 양방향 TCP)
    - 전송 제어 프로토콜, 전송계층에 속한다. 네트워크의 정보 전달 통제 프로토콜
    - OSI7 Layer 4계층, TCP가 실을 수 있는 데이터 -> 세그먼트(Segment)

    ※  소 -> 소켓(socket)
        말 -> 바인더(binder)
        리 -> 리슨(Listen)
        아 -> 아댑터(adapter)

    - 3-way handshake

  ![TCP001](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/TCP001.png)

    - 송수신자 확인 뒤 데이터를 주고 받음

- IP란?? => Internet Protocol 인터넷에 연결되어 있는 모든 장치들을 식별할 수 있도록 각 장비에 부여되는 고유주소!
    - IPv4, IPv6, Subnet Mask, Gateway, DNS

- 프로토콜(Protocol) => 대화에 필요한 통신규약
    - PF_INET = IPv4 인터넷 프로토콜 체계! <사실상 이것만 알면 됨>

- 소켓(Socket)
    - TYPE 
        - 연결지향형 소켓(SOCK_STREAM)
        - 비 연결지향형 소켓(SOCK_DGRAM)
 
## 2일차

- OSI-7 Layer(계층)
    - LINK 계층 - LAN, WAN, MAN 프로토콜 정의 영역
    - IP 계층 - 비 연결지향적 신뢰할 수 없는 프로토콜, 데이터를 전송할 때마다 거쳐야 할 경오를 선택, 그 경로는 일정치 않음
    - TCP/UDP 계층 - 전송계층으로 위의 TCP와 UDP의 차이로 설명가능

![TCP002](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/TCP002.png)


## 3일차

- TCP 기반 Half-close
    - TCP에서는 연결과정보다 중요한 것은 종료과정 
    - Half-close
    1) 일반종료
    2) 완전종료

- 소켓, 스트림
    - 스트림 : 송수신이 가능한 상태를 일종의 스트림, 물의 흐름
    - 소켓 : 양한쪽 방햐응로만 데이터 이동 가능
    - 즉 양방햐을 위해서는 두개의 스트림이 필요함

- DNS(Domain Name System)

![TCP003](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/TCP003.png)


- 소켓의 다양한 옵션

![TCP004](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/TCP004.png)

- 프로세스 : 컴퓨터에서 실행중인 프로그램

## 4일차

- 멀티태스킹 기반의 다중접속 서버
    - 서버
    
    ![멀티태스킹 서버](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/multi001.png)

    - 클라이언트

    ![멀티태스킹 클라이언트](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/multi002.png)

    - select 함수의 기능과 호출순서
        - select 함수를 사용하면 한곳에 여러개의 파일 디스크립터를 모아놓고 동시에 관찰할 수 있다.
        - 관찰항목 각각을 가리켜 이벤트라고 한다.

        - 호출순서
            1. 파일 디스크립터의 설정, 검사의 범위 지정, 타임아웃의 설정
            2. select 함수의 호출
            3. 호출결과 확인

        ![select 클라이언트](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/select001.png)

## 5일차
- 입출력 함수
    - send & recv 함수

    ```c
    ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
    // sockfd : 데이터 전송 대상과의 연결을 의미하는 소켓의 파일 디스크립터 전달
    // buf : 전송할 데이터를 저장하고 있는 버퍼의 주소 값 전달
    // nbytes : 전송할 바이트 수 전달
    // flags : 데이터 전송 시 적용할 다양한 옵션 정보 전달

    ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
    // sockfd : 데이터 수신 대상과의 연결을 의미하는 소켓의 파일 디스크립터 전달
    // buf : 수신된 데이터를 저장할 버퍼의 주소 값 전달
    // nbytes : 수신할 수 있는 최대 바이트 수 전달
    // flags : 데이터 수신 시 적용할 다양한 옵션 정보 전달
    ```
    - 옵션
        - MSG_OBB
            - 긴급 데이터(Out-of-band data)의 전송을 위한 옵션

        - MSG_PEEK
            - MSG_PEEK 옵션은 MSG_DONTWAIT 옵션과 함께 설정
            - 입력버퍼에 수신된 데이터가 존재하는지 확인하는 용도로 사용

        - MSG_DONTROUTE
            - 데이터 전송과정에서 라우팅 테이블을 참조하지 않을 것을 요구하는 옵션
            - 로컬 네트워크 상에서 목적지를 찾을 때 사용되는 옵션

        - MSG_DONTWAIT
            - 입출력 함수 호출과정에서 블로킹 되지 않을 것을 요구하기 위한 옵션
            - 넌-블로킹 IO의 요구에 사용되는 옵션

        - MSG_WAITALL
            - 요청한 바이트 수에 해당하는 데이터가 전부 수신될 때까지 호출된 함수가 반환되는 것을 막기 위한 옵션

    - readv & writev 함수
        - 데이터를 모아서 전송, 모아서 수신하는 기능의 함수
        - writev 함수를 사용하면 여러 버퍼에 나뉘어 저장되어 있는 데이터를 한번에 전송할 수 있고
        - readv 함수를 사용하면 데이터를 여러 버퍼에 나눠서 수신할 수 있다.

- 표준 입출력 함수의 장점
    - 표준 입출력 함수는 이식성이 좋다.
    - 표준 입출력 함수는 버퍼링을 통한 성능의 향상에 도움이 된다.
        - 버퍼링은 데이터를 묶어서 전송하는 것을 말한다.

- 표준 입출력 함수의 단점
    - 양방향 통신이 쉽지 않다.
    - 상황에 따라서 fflush 함수의 호출이 빈번히 등장할 수 있다.
        - 버퍼링 문제로 인해서 읽기에서 쓰기로, 쓰기에서 읽기로 작업의 형태를 바꿀 때마다 fflush 함수를 호출해야하기에 성능에 영향을 준다.
    - 파일 디스크립터를 FILE 구조체의 포인터로 변환해야한다.

    fflush : 출력버퍼를 비운다.

- 입출력 스트림 분리
    - 이점
        - 읽기모드와 쓰기모드의 구분을 통한 구현의 편의성 증대
        - 입력버퍼와 출력버퍼를 구분함으로 인한 버퍼링 기능의 향상
        - 스트림 분리방법이나 분리 목적이 달라지면 이점도 달라진다.

    - Half-close
        - Half close, 말 그대로 반만(Half) 닫는다(Close) 라는 뜻이다. 즉, 두 개의 스트림 중 하나만 닫아서 한 쪽 스트림은 열어두는 상태를 뜻한다.
        - A가 데이터를 모두 보내고, A의 입력 스트림을 닫음으로써 B에게 EOF를 전달한다.
        - B는 EOF를 확인하고, 데이터 수신의 끝임을 알 수 있고, 메시지를 보내면 된다.

    - 스트림 종료 시 Half-close가 진행되지 않은 이유
        - 읽기 모드 FILE 포인터와 쓰기모드 FILE 포인터는 하나의 디스크립터를 기반으로 생성되었기 때문에 어떠한 FILE 포인터를 대상으로 fclose 함수를 호출하더라도 파일 디스크립터가 종료되고, 이는 소켓의 완전 종료로 이어진다.

        ![FILE 포인터관계](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/16001.png)

    - Half-close를 위한 모델
        -  파일 디스크립터를 복사한 다음에 가각의 파일 디스크립터를 대상으로 FILE 포인터를 만들면, FILE 포인터 소멸 시 해당 파일 포인터에 연결된 파일 디스크립터만 소멸된다.

        ![Half-close를 위한 모델](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/16002.png)

    - 파일 디스크립터 복사
        - 파일 디스크립터 복사는 fork 함수호출 시 진행되는 복사와는 차이가 있다.
        - fork 함수호출 시 진행되는 복사는 프로세스를 통째로 복사하는 상황에서 이뤄지기 때문에 하나의 프로세스에 원본과 복사본이 모두 존재하지 않는다.
        - 하지만 dup 함수는 프로세스의 생성을 동반하지 않는 원본과 복사본이 하나의 프로세스 내에 존재하는 형태의 복사가 가능하다.

## 6일차
- epoll의 이해와 활용
    - select 함수의 단점을 극복한 것이 epoll의 장점
        - 상태변화의 확인을 위한, 전체 파일 디스크립터를 대상으로 하는 반복문이 필요없다.
        - select 함수에 대응하는 epoll_wait 함수 호출 시, 관찰대상의 정보를 매번 전달할 필요가 없다.

    - epoll 함수
        - epoll_create : epoll 파일 디스크립터 저장소 생성
        - epoll_ctl : 저장소에 파일 디스크립터 등록 및 삭제
        - epoll_wait : select 함수와 마찬가지로 파일 디스크립터의 변화를 대기한다.

    - 레벨 트리거와 엣지 트리거
        - Level Trigger : 입력 버퍼에 데이터가 남아있는 동안에 계속해서 이벤트를 발생시킨다.
        - Edge Trigger : 입력 버퍼에 데이터가 들어오는 순간 딱 한번만 이벤트를 발생시킨다.

        - 엣지 트리거 기반의 서버 구현을 위해서 알아야 할 것 두가지
            1. 변수 errno을 이용한 오류의 원인을 확인하는 방법
                - read 함수는 입력버퍼가 비어서 더 이상 읽어 들일 데이터가 없을 때 -1을 반환하고, 이 때 errno에는 상수 EAGAIN가 저장된다.
            2. 넌-블로킹(Non-blocking) IO를 위한 소켓의 특성을 변경하는 방법
                - 파일을 넌-블로킹 모드로 변환하기 위해선 다음 두문장을 실행하면 된다.

                ```C
                int flag = fcntl(fd, F_GETFL, 0); // 특성정보를 받아오기
                fcntl(fd, F_SETFL, flag|O_NONBLOCK); // 논블로킹 특성 재설정
                ```

- 멀티 쓰레드 기반의 서버구현
    - 쓰레드의 등장 배경
        1. 프로세스 생성이라는 부담스러운 작업과정을 거친다.
        2. 두 프로세스 사이의 데이터 교환이 어렵다.
        3. 컨텍스트 스위칭에 따른 프로세스 생성 방식은 비효율적이다.
    
    - 쓰레드의 장점
        1. 경량화된 프로세스로 생성 및 컨텍스트 스위칭이 보다 빠르다.
        2. 쓰레드 사이의 데이터 교환은 특별한 기법이 필요치 않다.

    - 쓰레드와 프로세스의 차이점
        - 프로세스는 서로 완전히 독립적이다, 프로세스는 운영체제 관점에서의 실행흐름을 구성한다.
        - 쓰레드는 프로세스 내에서의 실행 흐름을 갖는다, 데이터 영역과 힙 영역을 공유하기 때문에 컨텍스트 스위칭에 대한 부담이 덜하다. 또한 공유하는 메모리 영역으로 인해서 쓰레드간 데이터 교환이 매우 쉽게 이뤄진다.

        ![쓰레드와 프로세스 구조](https://raw.githubusercontent.com/breadcoffee/Linux-SocketProgramming-2024/main/images/18001.png)

    - 임계영역(Critical Section) : 둘 이상의 쓰레드가 동시에 실행하면 문제를 일으키는 문장이 하나 이상 존재하는 함수를 말함
        - 쓰레드에 안전한 영역과 불안전한 영역이 존재한다.

        ```C
        struct hostent *gethostbuname(const char *hostname); // 쓰레드에 불안전
        struct hostent *gethostbuname_r(const char *name, struct hostent *result, char *buffer, intbuflen, int *h_errnop); // 쓰레드에 안전
        ```

        - 워커 쓰레드 모델 : 하나의 전역변수를 두개의 쓰레드가 직접 접근하는 모델


