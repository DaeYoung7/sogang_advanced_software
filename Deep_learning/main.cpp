/*
*	Convolution Neural Network example
*/
#include"cnn.h"
#include<mnist.h>

int num_of_epoch = 50;

int main() {
	srand(1);		//디버깅을 위해 고정된 난수를 사용.
	int num_of_valid;
	MNIST* valid = ReadMNIST("./mnist/t10k-images.idx3-ubyte", "./mnist/t10k-labels.idx1-ubyte", &num_of_valid, 0);
	int num_of_train;
	MNIST* train = ReadMNIST("./mnist/train-images.idx3-ubyte", "./mnist/train-labels.idx1-ubyte", &num_of_train, 0);

	num_of_train /= 10; num_of_valid /= 10;					//이번 실습도 마찬가지로 시간 관계상 데이터의 1/10만 사용합니다.

	//INPUT = 28x28x1
	//5x5 kernel을 사용.
	//kernel_depth의 크기만큼 depth가 결정됨.
	//C1의 depth는 6, C2의 depth는 12
	////////////////////////////////////////////////////////////////////////////////
	//
	//
	// PROBLEM 1: EXPLAIN
	//
	// 아래의 kernel_depths[] 변수에 순서대로 6, 72가 들어가 있습니다.
	// 그러나 C1의 depth는 6이고 C3의 depth는 12가 됩니다.
	// 왜 C2의 depth가 72가 아닌 12가 되는지 실습 검사 맡으실 때 조교한테 설명해 주시면 됩니다.
	// 
	//
	//
	////////////////////////////////////////////////////////////////////////////////

	int kernel_depths[] = { 6, 72 };
	CNN cnn = CreateCNN(28, 1, 2, kernel_depths, 5);

	//ReadParameters(&cnn,"parameter.txt");
	float learning_rate = 0.04F;
	//tip : train, valid가 96%가 넘었을때 learing_rate를 낮춰는 방식의 최적화 가능.
	for (int e = 1; e <= num_of_epoch; e++) {
		int answer = 0;
		for (int j = 0; j < num_of_train; j++) {
			int a = ForwardCNN(&cnn, train[j].image);
			if (a == train[j].label) {
				answer++;
			}
			BackwardCNN(&cnn, train[j].label, learning_rate);
		}
		printf("epoch = %d\ttrain : %f\t", e, (float)answer / num_of_train);
		answer = 0;
		for (int j = 0; j < num_of_valid; j++) {
			int a = ForwardCNN(&cnn, valid[j].image);
			if (a == valid[j].label) {
				answer++;
			}
		}
		printf("validation : %f", (float)answer / num_of_valid);
		puts("");
		//WriteParameters(&cnn,"parameter.txt");
	}
	return 0;
}