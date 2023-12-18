#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

struct client {
	string name;
	int priority;
	time_t timestamp;
};

class printerqueue {
private:
	queue<client> printqueue;
	queue<client> printhistory;

public:
	void enqueue(client client) {
		printqueue.push(client);
	}

	void dequeue() {
		if (!printqueue.empty()) {
			client printedclient = printqueue.front();
			printqueue.pop();

			printhistory.push(printedclient);
			cout << "напечатанный: " << printedclient.name << " (" << printedclient.priority << ")" << endl;
		}
		else {
			cout << "очередь пуста!" << endl;
		}
	}

	void printstatistics() {
		cout << "статистика печати:" << endl;
		while (!printhistory.empty()) {
			client printedclient = printhistory.front();
			printhistory.pop();

			char buffer[80];
			tm localTime;
			localtime_s(&localTime, &printedclient.timestamp);
			asctime_s(buffer, sizeof(buffer), &localTime);

			cout << "напечатанный: " << printedclient.name << " (" << printedclient.priority << ") в " << buffer;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");
	printerqueue printer;

	// enqueue clients with different priorities
	client client1 = { "клиент: 1", 2, time(0) };
	client client2 = { "клиент: 2", 1, time(0) };
	client client3 = { "клиент: 3", 3, time(0) };
	printer.enqueue(client1);
	printer.enqueue(client2);
	printer.enqueue(client3);

	// dequeue clients for printing
	printer.dequeue();
	printer.dequeue();
	printer.dequeue();

	// print statistics
	printer.printstatistics();

	return 0;
}