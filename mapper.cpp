#include <iostream>
#include <cmath>
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

    void setOnCurve(bool isOnCurve)
    {
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
            cout << "| ";
        }
        else if (y == 0)
        {
            cout << "- ";
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
    for (int j = GRAPH_SIZE; j > 0; j--)
    {
        for (int i = 0; i < GRAPH_SIZE; i++)
        {
            graph[i][j].toString();
            if (i + 1 == GRAPH_SIZE)
            {
                cout << "\n";
            }
        }
    }
}

// ( x - h )^2 + ( y - k )^2 = r^2
// ... v
// y = k +- root(r^2 - x^2 + 2xh - h^2) where h = centerX, k = centerY
void equationOfCircle(GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE], float centerX, float centerY, int radius)
{
    int graphBuffer = GRAPH_SIZE / 2;
    for (int calcX = -(graphBuffer); calcX <= graphBuffer; calcX++)
    {
        double rootCoificient = sqrt(
            pow(radius, 2) - pow(calcX, 2) + (2 * calcX * centerX) - pow(centerX, 2)
            );
        //do + equation
        double calcY = centerY + rootCoificient;

        if (calcY <= graphBuffer && calcY >= -(graphBuffer))
        {
            int roundedY = round(calcY);
            graph[calcX + graphBuffer][roundedY + graphBuffer].setOnCurve(true);
        }

        //do - equation
        calcY = centerY - rootCoificient;

        if (calcY <= graphBuffer && calcY >= -(graphBuffer))
        {
            int roundedY = round(calcY);
            graph[calcX + graphBuffer][roundedY + graphBuffer].setOnCurve(true);
        }
    }
}

// ax^2+bx+c=0
void quadraticEquation(GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE], float a, float b, int constant)
{
    int graphBuffer = GRAPH_SIZE / 2;
    for (int calcX = -(graphBuffer); calcX <= graphBuffer; calcX++)
    {
        double calcY = (a * pow(calcX, 2)) + (b * calcX) + constant;
        if (calcY <= graphBuffer && calcY >= -(graphBuffer))
        {
            int roundedY = round(calcY);
            graph[calcX + graphBuffer][roundedY + graphBuffer].setOnCurve(true);
        }
    }
}

// y = mx + c
void equationOfLine(GraphPoint graph[GRAPH_SIZE][GRAPH_SIZE], float slope, int constant)
{
    int graphBuffer = GRAPH_SIZE / 2;
    for (int calcX = -(graphBuffer); calcX <= graphBuffer; calcX++)
    {
        double calcY = (slope * calcX) + constant;
        int roundedY = round(calcY);
        if (roundedY <= graphBuffer && roundedY >= -(graphBuffer))
        {
            graph[calcX + graphBuffer][roundedY + graphBuffer].setOnCurve(true);
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

    char chosenEquation;
    cout 
    << "Please choose graph type:\n"
    << "l for equation of a line,\n"
    << "q for quadratic,\n"
    << "c for circle:\n";

    cin >> chosenEquation;

    int chosenConst;
    switch (chosenEquation)
    {
    case 'l':
        float chosenSlope;
        int chosenConst;

        cout << "Please enter slope M: ";
        cin >> chosenSlope;

        cout << "Please enter constanc C: ";
        cin >> chosenConst;

        equationOfLine(graph, chosenSlope, chosenConst);
        break;

    case 'q':
        float coifA;
        float coifB;
        cout << "Please enter coificient A: ";
        cin >> coifA;

        cout << "Please enter coificient B: ";
        cin >> coifB;

        cout << "Please enter constant C: ";
        cin >> chosenConst;

        quadraticEquation(graph, coifA, coifB, chosenConst);

        break;
    case 'c':
        float centerX;
        float centerY;
        cout << "Please enter center of circle X: ";
        cin >> centerX;

        cout << "Please enter center of circle Y: ";
        cin >> centerY;

        cout << "Please enter the radius of the circle: ";
        cin >> chosenConst;

        equationOfCircle(graph, centerX, centerY, chosenConst);

        break;
    }

    printGraph(graph);
}