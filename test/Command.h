#pragma once
void* CommandThread(void* data)
{
	string input;
	while (isRunnig)
	{
		cin >> input;
		for (int i = 0; i < input.size(); i++)
		{
			// �ҹ��ڸ� ã�Ƽ�
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				// �ҹ��ڸ� �빮�ڷ� ����� �ݽô�!
				input[i] -= 'A' - 'a';
			}
		}
		switch (input.c_str())
		{
		case "QUIT":
		case "EXIT":
		case "END" :
			isRunnig = false;
			break;

		default:
			break;
		};
	};
}