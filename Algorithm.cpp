//
// Created by ahsan on 12/3/23.
//
#include "Algorithm.h"
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <utility>

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Sort class                                  *
 *                                                                                         *
 *******************************************************************************************/

void Sort::bubbleSort(int *array, int length) {
    for(int i=0;i<length;i++)
        for(int j=0;j<length-i-1;j++)
        {
            if(array[j]>array[j+1])
                Utility::swap(array[j], array[j+1]);
        }
}

void Sort::bubbleSort(SinglyLinkedList &list) {
    SinglyLinkedListNode* p = list.head;
    while(p!= nullptr)
    {
        SinglyLinkedListNode* q = p->next;
        while (q!= nullptr)
        {
            if(q->data<p->data)
                Utility::swap(p->data, q->data);
            q=q->next;
        }
        p=p->next;
    }
}

void Sort::cycleSort(int *array, int length) {
    for(int cycleStart = 0; cycleStart<length-1; cycleStart++)
    {
        int temp = array[cycleStart];
        while(true){
            int pos = cycleStart;
            for (int i = pos+1; i < length; i++)
                if (array[i] < temp)
                    pos++;
            if (pos == cycleStart)
                break;
            while (array[pos] == temp)
                pos++;
            Utility::swap(array[pos], temp);
        }
        array[cycleStart] = temp;
    }
}

void Sort::pancakeSort(int *array, int length) {
    for(int i=0;i<length-1;i++)
    {
        Array::flipArray(array, length, Array::maxIndex(array, length-i));
        Array::flipArray(array, length, length - 1 - i);
    }
}

void Sort::mergeSort(int *array, int length, int start, int end) { // NOLINT(*-no-recursion)
    end =(end==-1)?length-1:end;
    if(start==end)
        return;
    int middle = (start+end)/2;
    mergeSort(array, middle+1, start, middle);
    mergeSort(array, length-middle-1, middle+1, end);
    Array::sortedMerge(array, start, middle, end);
}

void Sort::quickSort(int *array, int length, int start, int end) { // NOLINT(*-no-recursion)
    end = (end==-9)?length-1:end;

    if(start<end)
    {
        int p_index = Partition(array, start, end);
        quickSort(array, length, start, p_index-1);
        quickSort(array, length, p_index+1, end);
    }
}

int Sort::Partition(int *array, int start, int end) {
    int pivot = array[end];
    int p_index = start;

    for(int i=start;i<end;i++)
    {
        if(array[i]<=pivot)
        {
            Utility::swap(array[i], array[p_index]);
            p_index++;
        }
    }
    Utility::swap(array[p_index], array[end]);
    return p_index;
}

void Sort::insertionSort(int *array, int length) {
    for(int i=1;i<length;i++)
    {
        int key = array[i];
        int j = i-1;
        while(j>=0 && array[j]>key)
        {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void Sort::selectionSort(int *array, int length) {
    for(int i=0;i<length-1;i++)
    {
        int* subArray = array + i;
        Utility::swap(array[i], array[Array::minIndex(subArray, length-i)+i]);
    }
}

void Sort::bucketSort(int *array, int length) {
    const int nBuckets = 10;
    const int min = Array::minElement(array, length);
    const int max = Array::maxElement(array, length);
    const int range = ceil((double)(max - min)/nBuckets);
    SinglyLinkedList bucket[nBuckets];

    for(int i=0;i<length;i++)
        bucket[(array[i]-min)/range].pushBack(array[i]);

    for(auto & i : bucket)
        Sort::bubbleSort(i);

    int j=0;
    for(auto & i : bucket)
    {
        SinglyLinkedListNode* p = i.head->next;
        while(p!= nullptr)
        {
            array[j++] = p->data;
            p=p->next;
        }
    }

}

void Sort::countingSort(int *array, int length) {
    const int max = Array::maxElement(array, length);
    int count[max+1];
    for(int& i : count)
        i = 0;
    for(int i=0;i<length;i++)
        count[array[i]]++;

    for(int i=0, j=0;i<=max;)
    {
        if(count[i]>0)
        {
            array[j++] = i;
            count[i]--;
        }

        else
            i++;
    }

}

void Sort::gnomeSort(int *array, int length) {
    int index = 0;
    while(index<length)
    {
        if(index==0)
            index++;
        if(array[index]>=array[index-1])
            index++;
        else
        {
            Utility::swap(array[index], array[index-1]);
            index--;
        }
    }
}

void Sort::pigeonHoleSort(int *array, int length) {
    const int min = Array::minElement(array, length);
    const int max = Array::maxElement(array, length);
    const int range = max-min+1;

    // making array of (queues of size 10) of size range
    auto* holes = new Queue[range];
    for(int i=0;i<range;i++)
        holes[i] = Queue(10);

    for(int i=0;i<length;i++)
        holes[array[i]-min].enqueue(array[i]);

    for(int i=0, k=0;i<range;i++)
    {
        while(!holes[i].isEmpty())
            array[k++] = holes[i].dequeue();
    }
}

void Sort::bitonicSort(int *array, int length, int start, int dir) {
    /* check if the log2(length) is a whole number else return*/
    double temp = log2(length);
    int temp2 = temp;
    if(temp-temp2 != 0)
    {
        cout<<"The number of elements for bitonic sort must be of order 2^n"<<endl;
        return;
    }

    if(length>1)
    {
        int middle = length/2;
        bitonicSort(array, middle, start, 0);
        bitonicSort(array, middle, start+middle, 1);

        bitonicMerge(array, start, length, dir);
    }
}

void Sort::bitonicMerge(int *array, int start, int length, int dir) {
    if(length>1)
    {
        int middle = length/2;
        for(int i=start;i<start+middle;i++)
        {
            if(dir==(array[i]<array[i+middle]))
                Utility::swap(array[i], array[i+middle]);
        }
        bitonicMerge(array, start, middle, dir);
        bitonicMerge(array, start+middle, middle, dir);
    }
}

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Print class                                 *
 *                                                                                         *
 *******************************************************************************************/

void Print::printArray(int *array, int length) {
    for(int i=0;i<length;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}

void Print::printLinkedList(SinglyLinkedList& list) {
    SinglyLinkedListNode* p = list.head;
    while(p != nullptr)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

void Print::printQueue(Queue& queue) {
    Queue temp(queue.getSize());
    temp = queue;
    while(!temp.isEmpty())
        cout<<temp.dequeue()<<" ";
    cout<<endl;
}

void Print::printArray(int **array, int width, int height) {
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
            cout<<array[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void Print::printStack(Stack &stack) {
    for(int i=0;i<=stack.top;i++)
        cout<<stack.array[i]<<" ";
    cout<<endl;
}

void Print::printVector(vector<int> &list) {
    for(auto& i:list)
        cout<<i<<" ";
    cout<<endl;
}

void Print::printBT(BinaryTree &tree)
{
    char s[tree.height() * 2][255];
    for (auto & i : s)
        sprintf(i, "%80s", " ");

    printTree(tree.root, 0, 0, 0, s);

    for (auto & i : s)
        printf("%s\n", i);
}

int Print::printTree(BTNode *tree, int is_left, int offset, int depth, char s[][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = printTree(tree->left, 1, offset, depth + 1, s);
    int right = printTree(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void Print::printGraph(const Graph &graph) {
    cout<<"Vertices: ";
    for(int i=0;i<graph.numVertices;i++)
        cout<<graph.vertices[i]<<", ";
    cout<<endl<<"Edges: "<<endl;
    for(int i=0;i< graph.numVertices;i++)
    {
        for(int j=0;j<graph.numVertices;j++)
        {
            if(graph.edges[i][j]!=0)
                cout<<graph.vertices[i]<<" -> "<<graph.vertices[j]<<" : "<<graph.edges[i][j]<<endl;
        }
    }
}

void Print::printGraph(const SpanningTree &graph) {
    cout<<"Vertices: ";
    for(int i=0;i<graph.getVertices();i++)
        cout<<graph.vertices[i]<<", ";
    cout<<endl<<"Edges: "<<endl;
    for(int i=0;i< graph.getVertices();i++)
    {
        for(int j=0;j<graph.getVertices();j++)
        {
            if(graph.edges[i][j]!=0)
                cout<<graph.vertices[i]<<" -> "<<graph.vertices[j]<<" : "<<graph.edges[i][j]<<endl;
        }
    }
}


/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Screen Coloring class                       *
 *                                                                                         *
 *******************************************************************************************/

void ScreenColoring::floodFill(int **screen, int width, int height, int pixelX, int pixelY, int newColor) {
    queue<Vector2i> toFill;
    Vector2i parent(pixelX, pixelY);
    int prevColor = screen[pixelX][pixelY];

    toFill.push(parent);

    while(!toFill.empty())
    {
        Vector2i current = toFill.front();
        toFill.pop();

        screen[current.x][current.y] = newColor;

        if (isValid(screen, width, height, current.x + 1, current.y, prevColor, newColor))
            toFill.push(Vector2i(current.x + 1, current.y));

        if (isValid(screen, width, height, current.x - 1, current.y, prevColor, newColor))
            toFill.push(Vector2i(current.x - 1, current.y));

        if (isValid(screen, width, height, current.x, current.y + 1, prevColor, newColor))
            toFill.push(Vector2i(current.x, current.y + 1));

        if (isValid(screen, width, height, current.x, current.y - 1, prevColor, newColor))
            toFill.push(Vector2i(current.x, current.y - 1));

    }
}

bool ScreenColoring::isValid(int **screen, int width, int height, int pixelX, int pixelY, int prevColor, int newColor) {

    if(pixelX<0 || pixelX>=width || pixelY<0 || pixelY>=height || screen[pixelX][pixelY]==newColor || screen[pixelX][pixelY]!=prevColor)
        return false;
    return true;
}

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Genetic Algorithms class                    *
 *                                                                                         *
 *******************************************************************************************/

const string GeneticAlgorithms::GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
string GeneticAlgorithms::naturalSelection(const string& target, int population_size) {
    srand(time(nullptr));
    int generation = 0;
    vector<Individual> population;
    for(int i=0;i<population_size;i++)
        population.push_back(random_gnome(target.size()));

    bool found = false;
    while(!found)
    {
        for(auto & i : population)
            i.calculateWeakness(target);
        sortOnWeakness(population);
        if(population[0].weakness <= 0)
        {
            found= true;
            break;
        }
        vector<Individual> nextGeneration;
        int fittest = (10*population_size)/100;
        for(int i=0;i<fittest;i++)
            nextGeneration.push_back(population[i]);

        int childs = (90*population_size)/100;
        for(int i=0;i<childs;i++)
        {
            int father = rand()%50;
            int mother = rand()%50;
            Individual child = Individual::mate(population[father], population[mother]);
            child.calculateWeakness(target);
            nextGeneration.push_back(child);
        }
        population = nextGeneration;
        cout<< "Generation: " << generation << "\t";
        cout<< "String: "<< population[0].chromosome <<"\t";
        cout<< "Weakness: "<< population[0].weakness << "\n";
        generation++;
    }
    cout<< "Generation: " << generation << "\t";
    cout<< "String: "<< population[0].chromosome <<"\t";
    cout<< "Weakness: "<< population[0].weakness << "\n";
    return population[0].chromosome;
}

Individual GeneticAlgorithms::random_gnome(int size) {
    Individual person;
    for(int i=0;i<size;i++)
        person.chromosome += mutatedGene();
    return person;
}

char GeneticAlgorithms::mutatedGene() {
    char gene = GENES[rand()%GENES.size()];
    return gene;
}

void GeneticAlgorithms::sortOnWeakness(vector<Individual> &population) {
    for(int i=0;i<population.size();i++)
        for(int j=0;j<population.size()-i-1;j++)
        {
            if(population[j].weakness>population[j+1].weakness)
            {
                Individual temp = population[j];
                population[j] = population[j+1];
                population[j+1] = temp;
            }
        }
}

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Chess class                                 *
 *                                                                                         *
 *******************************************************************************************/

bool Chess::allVisited(int (*board)[8]) {
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(board[i][j]==-1)
                return false;
    return true;
}

void Chess::printBoard(int (*board)[8]) {
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}

void Chess::knightTour(int x, int y) {
    int solution[8][8];
    for(auto & i : solution)
        for(int & j : i)
            j = -1;
    vector<Vector2i> moves;
    moves.push_back(Vector2i(2, 1));
    moves.push_back(Vector2i(1, 2));
    moves.push_back(Vector2i(-1, 2));
    moves.push_back(Vector2i(-2, 1));
    moves.push_back(Vector2i(-2, -1));
    moves.push_back(Vector2i(-1, -2));
    moves.push_back(Vector2i(1, -2));
    moves.push_back(Vector2i(2, -1));
    solution[x][y] = 0;
    if(solveKnightTour(solution, 0, 0, moves))
        printBoard(solution);
    else
        cout<<"No solution exists!"<<endl;
}

bool Chess::solveKnightTour(int solution[8][8], int x, int y, vector<Vector2i> moves) {
    static int move = 0;
    if(allVisited(solution))
        return true;
    for(int i=0;i<moves.size();i++)
    {
        Vector2i next(x+moves[i].x, y+moves[i].y);
        if(isSafe(next) && solution[next.x][next.y]==-1)
        {
            move++;
            solution[next.x][next.y] = move;
            if(solveKnightTour(solution, next.x, next.y, moves))
                return true;
            else
            {
                move--;
                solution[next.x][next.y] = -1;
            }
        }
    }
    return false;
}

bool Chess::isSafe(Vector2i &position) {
    if(position.x >=0 && position.y>=0 && position.x<=7 && position.y<=7)
        return true;
    return false;
}

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Search class                                *
 *                                                                                         *
 *******************************************************************************************/

bool Search::breadthFirstSearch(Graph &graph, int startVertex, int endVertex) {
    int start = graph.hasIndex(startVertex);
    int end = graph.hasIndex(endVertex);

    if(start<0 || end<0)
        return false;

    Queue queue(graph.getVertices());
    queue.enqueue(start);

    bool marked[graph.getVertices()];
    for(auto& i:marked)
        i = false;
    marked[start] = true;

    do {
        int current = queue.dequeue();
        if(current == end)
        {
            if(current==start)
            {
                if(graph.weightIs(graph.getVertex(current), graph.getVertex(end))==0)
                    return false;
            }
            return true;
        }
        else
        {
            vector<int> adjacentNodes = graph.getAdjacentVertices(graph.getVertex(current));
            for(int adjacentNode : adjacentNodes)
            {
                int index = graph.hasIndex(adjacentNode);
                if(!marked[index]) {
                    marked[index] = true;
                    queue.enqueue(index);
                }
            }
        }
    }while(!queue.isEmpty());
    return false;
}

bool Search::depthFirstSearch(Graph &graph, int startVertex, int endVertex) {
    int start = graph.hasIndex(startVertex);
    int end = graph.hasIndex(endVertex);

    if(start<0 || end<0)
        return false;

    Stack stack(graph.getVertices());
    stack.push(start);

    bool marked[graph.getVertices()];
    for(auto& i:marked)
        i = false;
    marked[start] = true;

    do {
        int current = stack.pop();
        if(current == end)
        {
            if(current==start)
            {
                if(graph.weightIs(graph.getVertex(current), graph.getVertex(end))==0)
                    return false;
            }
            return true;
        }
        else
        {
            vector<int> adjacentNodes = graph.getAdjacentVertices(graph.getVertex(current));
            for(int adjacentNode : adjacentNodes)
            {
                int index = graph.hasIndex(adjacentNode);
                if(!marked[index]) {
                    marked[index] = true;
                    stack.push(index);
                }
            }
        }
    }while(!stack.isEmpty());
    return false;
}

/*******************************************************************************************
 *                                                                                         *
 *                           Implementation of Shortest Path class                         *
 *                                                                                         *
 *******************************************************************************************/

MinDistance ShortestPath::DijkstrasAlgorithm(Graph &graph, int vertex) {
    MinDistance dPath;
    int start = graph.hasIndex(vertex);
    int numVertices = graph.getVertices();
    bool marked[numVertices];
    for(int i=0;i<numVertices;i++)
        marked[i] = false;
    for(int i=0;i<numVertices;i++)
    {
        dPath.prevVertex.push_back(start);
        dPath.distance.push_back(Graph::INF_EDGE);
    }
    dPath.distance[start] = 0;
    for(int i=0;i<numVertices-1;i++)
    {
        int minDistance = Graph::INF_EDGE;
        int currentIndex = Graph::INF_EDGE;
        for(int j=0;j<numVertices;j++)
            if(dPath.distance[j]<minDistance && !marked[j])
            {
                minDistance = dPath.distance[j];
                currentIndex = j;
            }
        if(currentIndex == Graph::INF_EDGE)
            break;
        marked[currentIndex] = true;
        int currentVertex = graph.getVertex(currentIndex);
        vector<int> adjacentVertices = graph.getAdjacentVertices(currentVertex);

        for(int adjacentVertice : adjacentVertices)
        {
            int index = graph.hasIndex(adjacentVertice);
            int distance = graph.weightIs(currentVertex, adjacentVertice);
            if(!marked[index] && (dPath.distance[currentIndex]+distance)<dPath.distance[index]) {
                dPath.distance[index] = dPath.distance[currentIndex] + distance;
                dPath.prevVertex[index] = currentIndex;
            }
        }
    }
    return dPath;
}

void ShortestPath::shortestPaths(MinDistance minDistance, Graph &graph, int vertex) {
    for(int i=0;i<graph.getVertices();i++)
    {
        string path;
        int currentIndex = i;
        int current = graph.getVertex(i);
        if(graph.getVertex(minDistance.prevVertex[i]) == vertex)
        {
            if(minDistance.distance[i]==Graph::INF_EDGE) {
                path = "No path";
                goto skip;
            }
        }
        while (true)
        {
            path+= to_string(current);
            if(current == vertex)
                break;
            path += " >- ";
            current = graph.getVertex(minDistance.prevVertex[graph.hasIndex(current)]);
        }
        std::reverse(path.begin(), path.end());
        skip:
        string d = minDistance.distance[i]==Graph::INF_EDGE ? "inf": to_string(minDistance.distance[i]);
        cout<<"Shortest path from vertex "<<vertex<<" to vertex "<<graph.getVertex(i)<<": "<<path<<"\t\tDistance: "<<d<<endl;
    }
}

int ShortestPath::shortestDistance(Graph &graph, int fromVertex, int toVertex) {
    MinDistance dPath = DijkstrasAlgorithm(graph, fromVertex);
    return dPath.distance[graph.hasIndex(toVertex)];
}

vector<int> ShortestPath::shortestPath(Graph &graph, int fromVertex, int toVertex) {
    MinDistance dPath = DijkstrasAlgorithm(graph, fromVertex);
    vector<int> path;
    int current = toVertex;
    while (true)
    {
        path.push_back(current);
        if(current == fromVertex)
            break;
        current = graph.getVertex(dPath.prevVertex[graph.hasIndex(current)]);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

MinDistance ShortestPath::BellmanFordAlgorithm(DirectedGraph &graph, int vertex) {
    MinDistance dPath;
    int start = graph.hasIndex(vertex);
    int numVertices = graph.getVertices();

    for(int i=0;i<numVertices;i++)
    {
        dPath.prevVertex.push_back(start);
        dPath.distance.push_back(Graph::INF_EDGE);
    }
    dPath.distance[start] = 0;

    // find shortest path
    for(int i=0;i<numVertices-1;i++)
    {
        MinDistance temp = dPath;
        for(int j=0;j<numVertices;j++)
            for(int k=0;k<numVertices;k++)
            {
                if(graph.edges[j][k]!=0)
                    if(dPath.distance[k] > dPath.distance[j] + graph.edges[j][k] && dPath.distance[j]!=Graph::INF_EDGE)
                    {
                        temp.distance[k] = dPath.distance[j] + graph.edges[j][k];
                        temp.prevVertex[k] = j;
                    }
            }
        dPath = temp;
    }

    // check for negative cycle
    for(int j=0;j<numVertices;j++)
        for(int k=0;k<numVertices;k++)
        {
            if(graph.edges[j][k]!=0)
                if(dPath.distance[k] > dPath.distance[j] + graph.edges[j][k] && dPath.distance[j]!=Graph::INF_EDGE)
                {
                    cout<<"Graph has a negative cycle!"<<endl
                        <<"Paths cannot be calculated!"<<endl;
                    for(auto& i:dPath.prevVertex)
                        i = start;
                    return dPath;
                }
        }
    return dPath;
}

UndirectedGraph ShortestPath::KruskalAlgorithm(Graph &graph) {

    int graphSize = graph.getVertices();
    UndirectedGraph mst(graphSize);
    mst.numVertices = graph.getVertices();
    mst.maxVertices = graph.maxVertices;
    for(int i=0;i<graphSize;i++)
        mst.vertices[i] = graph.vertices[i];
    vector<vector<int>> edgeList;
    for(int i=0;i< graphSize;i++)
        for(int j=0;j<graphSize;j++) {
            if(i<j)
                continue;
            if (graph.edges[i][j] != 0)
                edgeList.push_back({graph.edges[i][j], graph.vertices[i], graph.vertices[j]});
        }
    sort(edgeList.begin(), edgeList.end());
    DisjointSetUnion sets(Array::maxElement(graph.vertices, graphSize)+1);
    for(auto& edge : edgeList)
    {
        int weight = edge[0];
        int vertex1 = edge[1];
        int vertex2 = edge[2];
        if(sets.findSet(vertex1)!=sets.findSet(vertex2))
        {
            sets.unionSets(vertex1, vertex2);
            mst.edges[graph.hasIndex(vertex1)][graph.hasIndex(vertex2)] = weight;
            mst.edges[graph.hasIndex(vertex2)][graph.hasIndex(vertex1)] = weight;
        }
    }
    return mst;
}
