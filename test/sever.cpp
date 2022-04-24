//������ �����Ǹ� ������ ������ �մϴ�.
//�����Ƿ� ������ �ϴ� ������?
//�����¿� ������ �� ������ �ۺ�IP�� �ʿ�������, ������ �� ������
// ���� �������ѿ� ����IP�� �� �ſ��� ��� �̾߱⸦ �� �ʿ䰡 �ֽ��ϴ�.
// ���� IP�� ���⿡�ٰ� �Է����ֽø� �˴ϴ�.
#define SEVER_PRIVATE_IP "172.31.37.105"

//��ǻ�Ϳ��� ���ÿ� �������α׷��� �ڵ��ϰ� �ֽ��ϴ�.
//������ �ϰ� �־���� ��Ʈ��ũ�� ����ϰ� ����!
//�ٸ� ������ ���� �������ϴ�. �����Ǹ� ������ ��ȭ�� �õ��ϸ��! ���� �޽����� ���縵 ������, ������ ������ ���� �� ���� �����
//"��Ʈ"��� �ϴ� ���� ���� �޽������� ������ �� �ְ� �����
// �� ��  ��Ʈ�� �ָ� �� ���α׷��� �ٰԿ�~ �ϴ� ����!
//49152 !~ 65535 �� �����Ӱ� ����� �� �ִ� "���� ��Ʈ"�ϱ� �� ���̿� �ִ� ������ �������ٰԿ�!
#define SEVER_PORT 54177

// ���������� �޽����� ���� �̴ϴ�.
// �޽��� �������� ���� ���� �����! ��Ʈ��ũ �������� ���������� �ִµ� �������� �Ѱ谡 ������ ���ۿ� ����
// ���� �׷��Ա��� ū �޽����� ���� ������ ���� �Ŵϱ� ������ �ִ� ���ۻ���� �������ֵ��� �սô�.
#define MAX_BUFFER_SIZE 1024

// �ִ밪�� ���ؾ��ϴ� �ٸ� ���� ���� �ſ���!
#define MAX_USER_NUMBER 100

#include <iostream>

//���� �����쿡�� �ȳ��ɴϴ�. ���������� ����� ����� �帮�� �ִ� �ſ���
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

using namespace std;

// poll�̶�� �ϴ� ���� ������ ������ ���־��� ��! �ν��ؼ� �����ִ� �����̿���
// ������ ������ �޽����� �������� �� ���� ������ ���ư����� 
// FD�� ������? File Descripter ������ �������ִ� �༮�̿�?
// ������ ����ȭ�� ���ε�! �������� �����̶�� �ϴ� �͵� ������ ���� ���·� ������ �մϴ�.
// ���� ��ȣ�� ������ �� �ִ� ������ �ɰſ���! ���Ͽ� �ش�Ǵ� ���� ��ȣ
struct pollfd pollFDArray[MAX_USER_NUMBER];

// ��⸸ �ϴ� fd�� �ʿ��ؿ�
// ��� �̻��� �갡 �ͼ� �̾߱⸦ �ϸ� �ȵ��߰���!
// ��ǻ�ʹ� ó�� ���� ip�� �ͼ� �̾߱��ϸ� "��ȭ �߸��ż̾��!" ��� �ϸ鼭 ���������
// ListenFD��� �ϴ� �ִ� �� ����� �̴ϴ�.
// ����! �� ���� ���� ������ �ϰ� �����Ű� ���ϴ�.
// �ٸ� FD���� ���ο� ������ �Ʒ��ִ� ���Ϸ� �� �ſ��� (�Ա� ������ �ϴ°ſ���)
// 0��° ������ ������������ ����� �̴ϴ�!
struct pollfd& ListenFD = pollFDArray[0];

// ���� ������ �����ϴ� ����(����)
char buffRecv[MAX_BUFFER_SIZE] = { 0 };
// ���� ������ �����ϴ� ����(����)
char buffSend[MAX_BUFFER_SIZE] = { 0 };

//���� ���� ��
unsigned int currentUserNumber = 0;

void EndFD(struct pollfd* targetFD);
int StartServer(int currentFD);


// �� #include�� ���⿡ �ֳ���?
//�ش��� ���� �ٿ��ֱ�� ���⿡ �־�� ���� �ִ� �������� ����� �� �־ ���⿡ �׾��!
#include "Messege.h"
#include "User.h"

int main()
{
	
	//					IPv4(4����Ʈ¥�� IP) 
	ListenFD.fd = socket(AF_INET, SOCK_STREAM, 0);
	ListenFD.events = POLLIN;
	ListenFD.revents = 0; 

	// 0�� ���������̴ϱ�!
	for (int i = 1; i < MAX_USER_NUMBER; i++)
	{
		//File Descripter�� ��ϵ��� ���� pollFD�¿� ������ �� �� ������
		// �ش�Ǵ� ��Ĺ�� ���ٴ� ���Դϴ�.
		pollFDArray[i].fd = -1;
	};

	//���⼭ FD�� �غ� �Ǿ��� ������ �������ô�.
	// ���� ������ ������ �������ָ鼭 ������ ������ �ſ���
	StartServer(ListenFD.fd);

	while (true)
	{
		//poll�� ���ؼ� ������ �߸���! ������ ������ �޽����� �������� �� ����!
		// 0�������� ���� �־ ���� ���Ͽ� ����� ���� ������ �� �� �ְ� ������ ����������!
		int result = poll(pollFDArray, MAX_USER_NUMBER, -1);

		// ������ �õ��ϰ� �;��ϴ� ������ ���� �غ��մϴ�! ���ο� ������ ����� ���� ����?
		struct sockaddr_in connectSocket;
		// �����ϰ����ϴ� ���Ͽ� �ּ� ������
		socklen_t addressSize;

		//���� �θ��µ���? 0�̸� �ƹ��� �����ߴ�! 15����ϸ�, 15���� �θ���!
		if (result > 0)
		{
			//���� ���Ͽ� ���� Ȯ��
			//������ ������ �õ��ϰ� �ֽ��ϴ�.
			if (ListenFD.revents == POLLIN)
			{
				cout << "Someone Connected!" << endl;
				//����� ������! �����¿� ������ �ö���� �ʹٸ� ��� �����ǰ� �ƴ϶�� �Ѵٸ��.. �� �޾���� �մϴ�.
				int currentFD = accept(ListenFD.fd, (struct sockaddr*)&connectSocket, &addressSize);

				//0���� ���� �������� ���� �վ ��ü ���� ���� -1�� ���¿��� ���ҰԿ�!
				if (currentUserNumber < MAX_USER_NUMBER - 1)
				{
					// 0�� ���� �����̴ϱ�!
					for (int i = 1; i < MAX_USER_NUMBER; i++)
					{
						//��� �ִ� pollFD�� ã�� �ſ���!
						if (pollFDArray[i].fd == -1)
						{
							// �̰� ����? ���� �ֳ�?
							if (userArray[i] != nullptr)
							{
								//������ Ȥ�� �������� ����� �� �־��� ���������� ���Կ�!
								delete userArray[i];
							}

							//���� �����Ҥ� ������ File Descriptor�� �޾ƿ���!
							pollFDArray[i].fd = currentFD;
							pollFDArray[i].events = POLLIN;
							pollFDArray[i].revents = 0;

							//������ ���� ������ֵ��� �սô�!
							userArray[i] = new User(i);

							cout << "Connected " << i << endl;


							//���� �Ѹ� �߰�
							++currentUserNumber;
							// �Ұ� �����ϱ� �����!
							break;
						};
					};
				};
			};

			// �� ������ ���� �����ϴ� ���� ���� �����̾�����
			// �Ʒ������� �ٸ� �Ϲ� �������� �����ϴ� �κ��� �ʿ��� �ſ���!
			for (int i = 1; i < MAX_USER_NUMBER; i++)
			{
				//����� �������� ����
				switch (pollFDArray[i].revents)
				{
					//��� ���� ����
				case 0: break;
					//���� ���� ����
				case POLLIN:
				{
					// ���� �����̿������� Ȯ���غ��߰���!
					//							�б� ����				  ���� ���� ��û!
					if (read(pollFDArray[i].fd, buffRecv, MAX_BUFFER_SIZE) < 1)
					{
						// ���޶���ϴµ� �� ��
						EndFD(&pollFDArray[i]);
						break;
					};

					//���޶�� �ϴ°� �ƴϰ� �ٸ� �� ��Ź���� �� ���⿡�� �޽����� ó���� �ʿ䰡 �ֱ���
					//BroadCastMessage(buffRecv, sizeof(buffRecv));
					int leftSize = sizeof(buffRecv);
					int checkSize = 0;
					while (leftSize > 0)
					{
						// ���� ���� üũ�� ĭ �������� 0 1 2 3
						char header[4];
						header[0] = buffRecv[0 + checkSize];
						header[1] = buffRecv[1 + checkSize];
						header[2] = buffRecv[2 + checkSize];
						header[3] = buffRecv[3 + checkSize];

						//					�����̸鼭 ���� ������!
						int currentSize = translateMessage(i, buffRecv + checkSize, leftSize, ProcessMessage(header));

						checkSize += currentSize;
						leftSize -= currentSize;
					};

					// �Է� ���� �ʱ�ȭ
					memset(buffRecv, 0, sizeof(buffRecv));
					//�Է� �ذ��������ϱ�  �� ������ ����.
					pollFDArray[i].revents = 0;
					break;
					// �̻��� ���� ���� ����!
				}
				default:
					EndFD(&pollFDArray[i]);
					break;
				};
			};
		};
	};

	//���� ���� �ݰ�
	close(ListenFD.fd);
	for (int i = 0; i < MAX_USER_NUMBER; i++)
	{
		// ���� �־�? �ݾ�!
		if (pollFDArray[i].fd != -1) close(pollFDArray[i].fd);
	}

	return -4;
}

int StartServer(int currentFD)
{
	// ������ �����Ϸ��� �ϴµ�... �ƴ�!
	// ���������� �����־��!
	if (currentFD == -1)
	{
		//���� ������ ������ �����!
		perror("socket()");
		//Ȥ�� �𸣴� ���� ���ֱ�
		close(currentFD);
		return -1;
	};

	//���Ͽ��ٰ� INET�̶�� ������ �־�Z�µ���
	//�׷�.. 4����Ʈ¥�� ip �� ���� �ưڴµ�.. �׷��� IP�� ����?
	// �׷��� ����� ������ ip�� ���� ���Ͽ��ٰ� ����� ���־�� �մϴ�.
	sockaddr_in address;

	//���� �𸣴ϱ� ���� �ʱ�ȭ �س��� ������ �����Կ�
	//address ���θ� ���� 0���� ���߱�
	memset(&address, 0, sizeof(address));

	//�����̶� ������ ������ �����ֵ��� �ҰԿ�
	address.sin_family = AF_INET;
	//���� ���� ip�� ���⿡�� �־��ֵ��� �սô�.
	address.sin_addr.s_addr = inet_addr(SEVER_PRIVATE_IP);
	//��Ʈ���� �����־�� �߾���?
	address.sin_port = htons(SEVER_PORT);

	// �ּҰ� ���⿡�� �� �����ٸ� ������ ������ �ȵ� �ſ���! ���常 �� ���̿�!
	// ����ؼ� ������ ������ �� �Ŵϱ�
	// ���� ������ �ּҸ� ���Ͼִٰ� "����" �� �ſ���      
	//                                                                ����!!
	if (bind(currentFD, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		perror("bind()");
		close(currentFD);
		return -1;
	};

	//������ ���� ������ �۵��� ���Ѻ��ϴ�.
	// �׷� ��¥�� ������ ���ư��� �Ű���?
	if (listen(currentFD, 8) == -1)
	{
		perror("listen()");
		close(currentFD);
		return -1;
	};

	cout << "sever is On the way" << endl;

	// ����� ��� �÷��� �̰ܳ������ϴ�.
	return 1;
}

void EndFD(struct pollfd* targetFD)
{
	//�ݾ��ֱ�
	close(targetFD->fd);

	// �ݾҽ��ϴ�. -1�� ǥ���ϱ�!
	targetFD->fd = -1;
	targetFD->revents = 0;

	//�������ϱ� �� �ٿ��ֱ�
	--currentUserNumber;

	cout << "User Connection has Destroyed" << endl;
}