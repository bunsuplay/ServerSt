#pragma once

 enum CommandType
{
	Error,
	Quit,


};
 // 현제 계산중인 
 CommandType currentType;
 // 현제 몇페이지 까지 읽었는가?
 int currentIndex;

 void CalculateCommand(string word)
 {
	 

	 if (currentIndex == 0)
	 {
		 if (word == "QUIT" || word == "EXIT" || word == "END" || word == "CLOSE")
		 {
			 currentType = CommandType::Quit;
		 };

	 };
	 ++currentIndex;
 }

 void ExitcutComaand()
 {
	 switch (currentType)
	 {
	 case CommandType::Quit:
		 isRunnig = false;
		 break;
	 case CommandType::Error:
		 break;
	 default:
		 break;
	 }
 }

void* CommandThread(void* data)
{
	string input;
	while (isRunnig)
	{
		// 관리자의 입력을 받음
		cin >> input;

		// 현제 계산중인 
		 currentType = CommandType::Error ;
		// 아직 받은 것이 없으니까 0번째!
		 currentIndex = 0;


		for (int i = 0; i < input.size(); i++)
		{
			// 소문자를 찾아서
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				// 소문자를 대문자로 만들어 줍시다!
				input[i] += 'A' - 'a';
			}
		}

		string currentWord;
		for (int i = 0; i <= input.size(); i++)
		{
			//글자가 끝나거나 스페이스가 나오면 그자리에서 끊고 , 그자리에서 알아보기!
			if (i = input.size() ||  input[i] == ' ')
			{
				CalculateCommand(currentWord);
				currentWord.clear();
			}
			else // 스페이스가 안나오면 단어안에다가 글자를 추가할 겁니다!
			{
				currentWord += input[i];
			};
		};
		//글자를 전부 파악했으니 실행
		ExitcutComaand();
	};

	return nullptr;
}