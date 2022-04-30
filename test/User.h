class User* userArray[MAX_USER_NUMBER] = { nullptr };

class User
{
	int fdNumber;
	string name = "<NULL>";
	//로그인이 되었는가?
	bool isLogin = false;

public:
	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	bool SetLogIn(string wantName)
	{
		// 여기서는 제가 중복 로그인이라는 것을 방지해줄 필요가 있습니다!
		// 저희가 같은 이름의 사람이 들어온다거나 이사람이 이미 로그인 되었다고 한 상태에서
		// 다시 로그인을 시도했을 때 문제가 생겼다고 알려줄수 있겠죠!
		if (isLogin) return false;

		// 이름 설정에 실패 했습니다!
		if (!SetName(wantName)) return false;
	}

	//해당 이름이 유효한지 체크하기
	bool CheckNameValidate(string wantName)
	{
		// 이름이 너무 깁니다!
		if (wantName.length() > 16)return false;

		int leftUser = currentUserNumber;
		for (int i = 0; i < MAX_USER_NUMBER; i++)
		{
			// 얘 저랑 이름이 똑같아요!
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
		if (!CheckNameValidate(wantName))return false;
		name = wantName;
		return true;
	};
};