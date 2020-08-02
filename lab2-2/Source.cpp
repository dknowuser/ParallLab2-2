#include <mpi.h>
#include <iostream>
#include <Windows.h>

using namespace std;

const int source = 99;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank = 0, processCount = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank != 1) {
		for (int i = 0; i < processCount; i++) {
			if (rank == i) { continue; };

			MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			//cout << "Process " << rank << " sent its rank to process " << i << endl;
		};
	}
	else {
		MPI_Request request;
		int flag = 0;
		int receivedRank = 0;
		MPI_Irecv(&receivedRank, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &request);

		while (!flag) {
			MPI_Test(&request, &flag, MPI_STATUSES_IGNORE);

			if (flag) {
				cout << "Received message from process 99." << endl;
			}
			else {
				cout << "I\'m still waiting..." << endl;
			};
		};
	};

	MPI_Finalize();
	return 0;
};