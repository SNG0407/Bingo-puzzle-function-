#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};
enum LINE_NUMBER
{
	//가로
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	//세로
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	//대각선
	LN_LT,
	LN_RT
};
int main()
{
	srand((unsigned int)time(0));
	int bingoBoard[25] = {};
	for (int i = 0; i < 25; i++) {
		bingoBoard[i] = i + 1;
	}
	// AI's bingo Board
	int AIBingoBoard[25] = {};
	for (int i = 0; i < 25; i++) {
		AIBingoBoard[i] = i + 1;
	}

	//suffle
	int Temp, index1, index2;
	for (int i = 0; i < 100; i++) {
		index1 = rand() % 25;
		index2 = rand() % 25;

		Temp = bingoBoard[index1];
		bingoBoard[index1] = bingoBoard[index2];
		bingoBoard[index2] = Temp;

		//AI suffle
		index1 = rand() % 25;
		index2 = rand() % 25;
		Temp = AIBingoBoard[index1];
		AIBingoBoard[index1] = AIBingoBoard[index2];
		AIBingoBoard[index2] = Temp;
	}


	// Game start
	int input;
	int AI_input = 0;
	int counter;
	int AICounter;
	int iAIMode;
	counter = 0, AICounter = 0;

	//AI 난이도 선택하기
	while (true) {
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";

		cin >> iAIMode;
		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	// Easy 모드는 숫자목록 중 *로 바뀌지 않은 숫자 목록을 만들어서 그 중 하나를 랜덤하게 선택하게 한다.
	// 선택 안된 목록 배열 만들기
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;
	while (true) {
		system("cls");
		cout << " ----------------------- Player ----------------------- " << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[i * 5 + j] == INT_MAX) {
					cout << "[*]" << "\t";

				}
				else {
					cout << "[" << bingoBoard[i * 5 + j] << "]" << "\t";
				}

			}
			cout << "\n";
		}
		cout << "Player Bingo Line : " << counter << endl << endl;
		cout << " AI가 선택 한 숫자 : " << AI_input << endl;
		cout << " ------------------------- AI ------------------------- " << endl;
		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AI Mode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AI Mode : Hard" << endl;
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (AIBingoBoard[i * 5 + j] == INT_MAX) {
					cout << "[*]" << "\t";

				}
				else {
					cout << "[" << AIBingoBoard[i * 5 + j] << "]" << "\t";
				}

			}
			cout << "\n";
		}
		cout << "AI Bingo Line : " << AICounter << endl << endl;

		if (counter >= 5) {
			cout << "Player won the bingo ! \nGame end." << endl;
			break;
		}
		else if (AICounter >= 5) {
			cout << "AI won the bingo ! \nGame end." << endl;
			break;
		}


		// get number from user
		cout << "Enter a number from 1 to 25 // 0 : Game end // ";
		cin >> input;
		if (input == 0) {
			break;
		}
		else if (input < 1 || input>25) {
			cout << "Please enter the usable number " << endl;
			continue;
		}

		//중복 찾기
		bool same = true; // 일단 전부 중복이라고 가정을 하고 처음엔 true로 논다.
		for (int i = 0; i < 25; i++) {
			if (input == bingoBoard[i]) {
				//같은 숫자가 있는 경우엔 중복이 아니므로 false로 변경
				same = false;

				// 숫자를 *로 변경하기 위해 툭수한 값인 INT_MAX로 해준다.
				bingoBoard[i] = INT_MAX;

				//더이상 숫자 찾을 필요 없으니 for문 빠져나가기
				break;
				;
			}
		}
		// same 이 true이면 중복된 것이니 값 input을 다시 받게 continue한다.
		if (same) {
			continue;
		}
		// AI 중복 찾기
		for (int i = 0; i < 25; i++) {
			if (input == AIBingoBoard[i]) {
				AIBingoBoard[i] = INT_MAX;

				//더이상 숫자 찾을 필요 없으니 for문 빠져나가기
				break;
				;
			}
		}

		switch (iAIMode)
		{
		case AM_EASY:
			// 선택 안된 숫자 목록 만들기
			iNoneSelectCount = 0;  // 선택 안된 숫자 개수는 목록을 만들때 카운팅하기
			for (int i = 0; i < 25; i++) {
				//현재 숫자가 *이 아닌 경우
				if (AIBingoBoard[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = AIBingoBoard[i];
					iNoneSelectCount++;
				}
			}
			//for 문을 빠져나오게 되면 선택 안된 목록 & 선택 안된 개수가 만들어진다!
			//선택 안된 목록의 숫자 중 랜덤한 하나의 숫자를 얻어오기 위해 인덱스 랜덤하게 구하기
			input = iNoneSelect[rand() % iNoneSelectCount];
			AI_input = input;
			break;
		case AM_HARD:
			//현재 남은 숫자 중 빙고 줄 완성 가능성이 가장 높은 줄을 찾아서 그 숫자 중 하나를 *로 만든다.
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			// 가로 라인 중 가장 *이 많은 라인 찾기
			for (int i = 0; i < 5; ++i) {
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (AIBingoBoard[i * 5 + j] == INT_MAX)
						++iStarCount;
				}

				//별이 5개 미만이어야 빙고 줄 아님 
				//기존 가장 많은 라인보다 별이 더 많아야 새로 가장 많은 줄이 되니 라인 교체 후 저장된 별 수 교체
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = i; //가로 라인은 0~4까지
					iSaveCount = iStarCount;
				}
			}

			// 가로 라인 중 가장 * 이 많은 라인은 구했고, 이 라인과 세로 라인 중 가장 *이 많은 라인을 비교하자
			for (int i = 0; i < 5; ++i) {
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (AIBingoBoard[j * 5 + i] == INT_MAX)
						++iStarCount;
				}

				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = 5 + i; //세로 라인은 5~9까지
					iSaveCount = iStarCount;
				}
			}

			// 왼 -> 오른 쪽 대각선 
			iStarCount = 0;
			for (int i = 0; i < 25; i += 6) {
				if (AIBingoBoard[i] == INT_MAX)
					++iStarCount;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_LT;  // = 10 대각선 1 라인
				iSaveCount = iStarCount;
			}
			// 오른 -> 왼 쪽 대각선 
			iStarCount = 0;
			for (int i = 4; i <= 20; i += 4) {
				if (AIBingoBoard[i] == INT_MAX)
					++iStarCount;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_RT; // = 11 대각선 2 라인
				iSaveCount = iStarCount;
			}

			// 모든 라인 조사 완료하면 iLINE에 가장 *이 많은 줄이 저장 됨
			// 그 줄에 있는 *이 아닌 숫자 중 하나를 선택하게 한다.

			//가로줄 일 경우
			if (iLine <= LN_H5) {
				//가로줄은 0~4사이의 값
				for (int i = 0; i < 5; ++i) {
					if (AIBingoBoard[iLine * 5 + i] != INT_MAX) {
						input = AIBingoBoard[iLine * 5 + i];
						break;
					}
				}
			}
			//세로 줄일 경우
			else if (iLine <= LN_V5) {
				//세로줄은 5~9사이의 값
				for (int i = 0; i < 5; i++) {
					if (AIBingoBoard[i * 5 + (iLine - 5)] != INT_MAX) {
						input = AIBingoBoard[i * 5 + (iLine - 5)];
						break;
					}
				}
			}
			else if (iLine == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (AIBingoBoard[i] != INT_MAX) {
						input = AIBingoBoard[i];
						break;
					}
				}
			}
			else if (iLine == LN_RT) {
				for (int i = 4; i <= 20; i += 4) {
					if (AIBingoBoard[i] != INT_MAX) {
						input = AIBingoBoard[i];
						break;
					}
				}
			}
			AI_input = input;
			break;
		}
		// AI 숫자 선택 완료 -> 플레이어 & AI의 숫자를 * 로 바꿔준다.
		for (int i = 0; i < 25; i++) {
			if (bingoBoard[i] == input) {
				bingoBoard[i] = INT_MAX;
				break;
			}
		}
		for (int i = 0; i < 25; i++) {
			if (AIBingoBoard[i] == input) {
				AIBingoBoard[i] = INT_MAX;
				break;
			}
		}

		//빙고 줄 수는 매번 숫자 입력시 처음부터 새로 카운트 - counter을 매번 0으로 초기화 후 다시 줄 수 센다
		counter = 0;
		AICounter = 0;

		//가로, 세로 줄 수 구하기
		int iStar1 = 0, iStar2 = 0; // 가로 세로
		int iStar3 = 0, iStar4 = 0; // 대각선
		int iAIStar1 = 0, iAIStar2 = 0;
		int iAIStar3 = 0, iAIStar4 = 0;
		for (int i = 0; i < 5; i++) {
			// 대각선 1 : 0부터 24 자리까지는 6의 배수 i*6
			if (bingoBoard[6 * i] == INT_MAX) {
				iStar3++;
			}
			// 대각선 2 : 4부터 20까지 4의 배수 i*4
			if (bingoBoard[4 * i] == INT_MAX) {
				iStar4++;
			}
			// AI 대각선
			if (AIBingoBoard[6 * i] == INT_MAX) {
				iAIStar3++;
			}
			if (AIBingoBoard[4 * i] == INT_MAX) {
				iAIStar4++;
			}
			iStar1 = 0; iStar2 = 0;
			iAIStar1 = 0; iAIStar2 = 0;
			for (int j = 0; j < 5; j++) {
				//가로 별 개수를 구한다.
				if (bingoBoard[i * 5 + j] == INT_MAX) {
					iStar1++;
				}
				//세로 별 개수를 구한다.
				if (bingoBoard[j * 5 + i] == INT_MAX) {
					iStar2++;
				}
				//AI 줄 체크
				if (AIBingoBoard[i * 5 + j] == INT_MAX) {
					iAIStar1++;
				}
				if (AIBingoBoard[j * 5 + i] == INT_MAX) {
					iAIStar2++;
				}

			}
			if (iStar1 == 5) {
				++counter;
			}
			if (iStar2 == 5) {
				++counter;
			}
			if (iStar3 == 5) {
				++counter;
			}
			if (iStar4 == 5) {
				++counter;
			}
			if (iAIStar1 == 5) {
				++AICounter;
			}
			if (iAIStar2 == 5) {
				++AICounter;
			}
			if (iAIStar3 == 5) {
				++AICounter;
			}
			if (iAIStar4 == 5) {
				++AICounter;
			}
		}

	}
	return 0;
}