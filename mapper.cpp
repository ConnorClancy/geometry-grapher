#include <iostream>
using namespace std;

class GraphPoint
{
protected:
    int x = 0;
    int y = 0;
    bool onCurve = false;

public:
    GraphPoint() {}

    GraphPoint(int xIn, int yIn)
    {
        x = xIn;
        y = yIn;
        onCurve = false;
    }

    void setOnCurve(bool isOnCurve) {
        onCurve = isOnCurve;
    }

    void toString()
    {
        if (onCurve)
        {
            cout << "0 ";
            return;
        }
        if (x == 0)
        {
            cout << "- ";
        }
        else if (y == 0)
        {
            cout << "| ";
        }
        else
        {
            cout << ". ";
        }
    }
};

const int GRAPH_SIZE = 50;

void printGraph(GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE])
{
    for (int i = 0; i < GRAPH_SIZE; i++)
    {
        for (int j = 0; j < GRAPH_SIZE; j++)
        {
            graph[i][j].toString();
            if (j + 1 == GRAPH_SIZE)
            {
                cout << "\n";
            }
        }
    }
}

// y = mx + c
void equationOfLine(GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE], int slope, int constant)
{
    int graphBuffer = GRAPH_SIZE / 2;
    for (int calcX = -(graphBuffer); calcX <= graphBuffer; calcX++)
    {
        int calcY = (slope * calcX) + constant;
        if (calcY <= graphBuffer && calcY >= -(graphBuffer)) {

            graph[calcX+graphBuffer][calcY+graphBuffer].setOnCurve(true);

        }
    }
}

int main()
{

    GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE] = {{}};

    int currX = -(GRAPH_SIZE / 2);
    for (int i = 0; i < GRAPH_SIZE; i++)
    {

        int currY = -(GRAPH_SIZE / 2);
        for (int j = 0; j < GRAPH_SIZE; j++)
        {
            graph[i][j] = GraphPoint(currX, currY);
            currY++;
        }
        currX++;
    }

    equationOfLine(graph, 2,-2);

    printGraph(graph);
}