#pragma once

 enum CommandType
{
	Error,
	Quit,


};
 // ���� ������� 
 CommandType currentType;
 // ���� �������� ���� �о��°�?
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
		// �������� �Է��� ����
		cin >> input;

		// ���� ������� 
		 currentType = CommandType::Error ;
		// ���� ���� ���� �����ϱ� 0��°!
		 currentIndex = 0;


		for (int i = 0; i < input.size(); i++)
		{
			// �ҹ��ڸ� ã�Ƽ�
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				// �ҹ��ڸ� �빮�ڷ� ����� �ݽô�!
				input[i] -= 'A' - 'a';
			}
		}

		string currentWord;
		for (int i = 0; i <= input.size(); i++)
		{
			//���ڰ� �����ų� �����̽��� ������ ���ڸ����� ���� , ���ڸ����� �˾ƺ���!
			if (i = input.size() ||  input[i] == ' ')
			{
				CalculateCommand(currentWord);
				currentWord.clear();
			}
			else // �����̽��� �ȳ����� �ܾ�ȿ��ٰ� ���ڸ� �߰��� �̴ϴ�!
			{
				currentWord += input[i];
			};
		};
		//���ڸ� ���� �ľ������� ����
		ExitcutComaand();
	};

	return nullptr;
}