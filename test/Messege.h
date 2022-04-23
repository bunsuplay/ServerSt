
enum class MessageType
{
	chat,

	Length,// ���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};

void SeparateMessage()
{

}

void translateMessage()
{

}

//                                                 ���ο��� ������� �⺻������ true����!
//												�׷���.. üũ���ص� �ǰ���!
//												üũ�Ϸ��� FD�� �����Ǿ�� �Ǵϱ�!\
//												sendSelf�� false�� �ϰ� ������ sendFD�� 
//												�� ���ؾ� �� �̴ϴ�!
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//����� ������ �ο����� �˰� �ֽ��ϴ�.
	// ������ �� ���� �ʾƵ� �������� �� ������ �ߴٸ�
	// ���� ��.. �� �� �ʿ� �ֳ�!
	// ���� ������ send�� 1�� �÷��ְ�, ��������ŭ ���´ٸ� ������!
	// sendSelf�� false�� -> �������� �����ִ� �� �ƴϸ�! ������ �ϴ� ���� ������
	// ��������� �ϰ���! �������� ������ �� Ĩ�ô�!
	// �ݺ����� �� �� �� ��µ�.. ������..? �ϸ鼭 ������ �� �ſ���! �װ� �����ֱ�!
	int send = sendSelf ? 0 : 1;
	//          ����?    ture  : false
	//        �������� ����?  0���´�! : 1�� ���³���!

	// 0���� ���� ����!  �ִ�ġ���� ���ų� ,�Ǵ�   ���� ���� ����ŭ ���´ٸ�!
	for (int i = 1; i < MAX_USER_NUMBER; i++) // || send >= currentUserNumber; i++
	{
		// �������� �� ��������! �̶�� �Ҷ� ��ƿ� ������ �ִٸ� �Ѿ��!
		if (!sendSelf && i == sendFD) continue;

		if (pollFDArray[i].fd != -1)
		{
			// ������ ���� ���� �� "���� �ִ� ��"���� �׷��� wirte��� �θ���
			// ���� ������ Read�ϰ���?
			//    �����  ����       �޽���,     ����
			if (write(pollFDArray[i].fd, message, length))
			{
				//���´�!
				if (++send >= currentUserNumber) return;
			};

		};
	};
	cout << "Message Send To" << send << "User : " << message << endl;
}