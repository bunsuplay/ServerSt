class User* userArray[MAX_USER_NUMBER] = { nullptr };

class User
{
	int fdNumber;
	string name = "<NULL>";
	//�α����� �Ǿ��°�?
	bool isLogin = false;

public:
	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	bool SetLogIn(string wantName)
	{
		// ���⼭�� ���� �ߺ� �α����̶�� ���� �������� �ʿ䰡 �ֽ��ϴ�!
		// ���� ���� �̸��� ����� ���´ٰų� �̻���� �̹� �α��� �Ǿ��ٰ� �� ���¿���
		// �ٽ� �α����� �õ����� �� ������ ����ٰ� �˷��ټ� �ְ���!
		if (isLogin) return false;

		// �̸� ������ ���� �߽��ϴ�!
		if (!SetName(wantName)) return false;
	}

	//�ش� �̸��� ��ȿ���� üũ�ϱ�
	bool CheckNameValidate(string wantName)
	{
		// �̸��� �ʹ� ��ϴ�!
		if (wantName.length > 16)return false;

		int leftUser = currentUserNumber;
		for (int i = 0; i < MAX_USER_NUMBER; i++)
		{
			// �� ���� �̸��� �Ȱ��ƿ�!
			if (userArray[i] != nullptr)
			{
				if(userArray[i]->name == wantName) return false;
				--leftUser;
			}
		}

		return true;
	}

	bool SetName(string wantName)
	{
		if (!CheckNameValidate(wantname))return false;
		name = wantName;
		return true;
	};
};