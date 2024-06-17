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
- send & recv 입출력 함수
    ```c
    ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
    // sockfd : 데이터 전송 대상과의 연결을 의미하는 소켓의 파일 디스크립터 전달
    // buf : 전송할 데이터를 저장하고 있는 버퍼의 주소 값 전달
    // nbytes : 전송할 바이트 수 전달
    // flags : 데이터 전송 시 적용할 다양한 옵션 정보 전달
    ```
