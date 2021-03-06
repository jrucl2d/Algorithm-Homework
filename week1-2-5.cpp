#include<iostream> //2015112083 유성근
#include<vector>
using namespace std;

int k1[6]; // greedy에서 각 coin의 개수(출력할 답)
int k2[6]; // bruteforce에서 각 coin의 개수(출력할 답)

void greedy(int m, int d, int* c) {
	for (int i = 0; i < 6; i++) // 결과 저장할 배열 0으로 초기화
		k1[i] = 0;

	int tmp; // 임시 변수
	for (int i = 0; i < d; i++) {
		tmp = m / c[i]; // 전체 돈을 현재 동전으로 나눈다. 그 몫이 해당 동전을 최대로 몇 개 쓸 수 있는지(k값)
		m -= tmp * c[i]; // 해당 동전을 최대로 쓴 만큼의 값을 전체 돈에서 빼준다.
		k1[i] = tmp; // 결과 저장
	}

	cout << "greedy : ";
	for (int i = 0; i < d; i++)
		cout << k1[i] << " ";
}

void bruteforce(int m, int d, int* c) {
	for (int i = 0; i < 6; i++) // 결과 저장할 배열 0으로 초기화
		k2[i] = 0;

	int dp[200]; // 해당 index의 돈을 만드는 데 드는 최소의 동전 개수가 저장됨
	int changedCoins[200]; // 바뀐 동전을 저장

	for (int i = 1; i <= m; i++) // dp에는 최소값이 저장되어야 하므로 적당히 높은 수로 모두 초기화해준다.
		dp[i] = 10000;
	dp[0] = 0; // 0원을 만드는 경우는 동전을 사용하지 않는 경우이므로 0으로 초기화해준다.

	// O(Md)의 시간 복잡도로 구하기. 
	for (int i = 0; i < d; i++) // 현재 동전 종류를 인덱스로 접근
	{
		// j의 값은 내가 현재 가진 동전들을 이용해서 만들고 싶은 돈의 총액이다.
		// 현재 동전의 값(c[i])보다 작은 돈은 현재의 동전을 가지고 아무것도 할 수 없으므로 생략한다.
		// 따라서 j(내가 만들고 싶은 돈)는 c[i]부터 시작한다.
		for (int j = c[i]; j <= m; j++)
		{
			// 원래 j의 돈을 만드는 데 드는 최소 동전 개수와 'j - i동전(c[i])의 값'을 만들 때 드는
			// 최소 동전 개수(dp[j-c[i]])에 c[i]동전 하나를 추가(+1)했을 때의 개수를 비교했을 때
			// 후자가 더 개수가 적다면 dp 값을 갱신해준다. 
			// 이 때 dp를 이용해 구할 때는 다음 dp의 값이 이전 dp의 값에 영향을 받기 때문에 새로 사용한
			// 동전이 있을 때는 해당 돈을 만들 때 변화된 사용 동전을 changedCoins 배열에 저장해준다.
			if (dp[j] > dp[j - c[i]] + 1)
			{
				dp[j] = dp[j - c[i]] + 1;
				changedCoins[j] = c[i];
			} // 반복을 모두 돌고 나면 dp[m]에는 m 동전을 만드는 데 드는 최소 동전 개수가 저장된다.
		}
	}
	// 출력
	while (m > 0) {
		for (int i = 0; i < d; i++) {
			if (c[i] == changedCoins[m]) // m원을 만드는데 해당 동전이 사용되었으면 해당 인덱스의 결과값을 증가시킨다.
				k2[i]++;
		}
		m -= changedCoins[m]; // m은 그 동전을 사용하기 전의 값으로 만들어서 그 전의 값에는 어떤 동전을 사용했는지 또 파악한다.
	}
	cout << "// bruteforce : ";
	for (int i = 0; i < d; i++)
		cout << k2[i] << " ";
}

int main()
{
	int d = 6; // coin의 개수, 주어짐
	int c[6] = { 55, 22, 15, 10, 7, 1 }; // 동전 종류, 주어짐
	vector<int>ans; // 다른 m만 파악하기 위한 벡터

	for (int i = 1; i <= 100; i++) { // m을 1부터 100까지 반복
		cout << "M이 " << i << "일 때 ";
		greedy(i, d, c);
		bruteforce(i, d, c);
		int ans1 = k1[0] + k1[1] + k1[2] + k1[3] + k1[4] + k1[5];
		int ans2 = k2[0] + k2[1] + k2[2] + k2[3] + k2[4] + k2[5];
		if (ans1 == ans2) // 사용된 동전의 종류가 달라도 총 사용 개수가 같으면 같은 것으로 처리한다.
			cout << "같습니다.\n";
		else { cout << "다릅니다.\n"; ans.push_back(i); } // 다른 경우에는 벡터 ans에 해당 m의 값을 push 한다.
	}	
	cout << "다른 M : ";
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}