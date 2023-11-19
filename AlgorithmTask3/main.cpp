#include <iostream>
#include <climits>

// Определение структуры "Node" для односвязного списка
struct Node {
    int x, y; // Координаты узла в лабиринте
    Node* next; // Указатель на следующий узел в списке
};

// Функция для создания нового узла
Node* newNode(int x, int y) {
    Node* temp = new Node;
    temp->x = x;
    temp->y = y;
    temp->next = NULL;
    return temp;
}

// Функция для добавления элемента в конец очереди
void enqueue(Node** head, Node** tail, int x, int y) {
    Node* temp = newNode(x, y);
    if (*head == NULL) {
        *head = *tail = temp;
    }
    else {
        (*tail)->next = temp;
        *tail = temp;
    }
}

// Функция для удаления элемента из начала очереди
void dequeue(Node** head, Node** tail) {
    if (*head == NULL) return;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head == NULL) *tail = NULL;
    delete temp;
}

// Функция для проверки, является ли данная точка допустимой
bool isValid(int x, int y, int m, int n) {
    return (x >= 0 && x < m && y >= 0 && y < n);
}

// Функция для поиска кратчайшего пути из лабиринта
int shortestPath(int** maze, int sx, int sy, int m, int n) {
    Node* head = NULL, * tail = NULL;
    int dx[] = { -1, 0, 1, 0 }; // Возможные направления движения по x
    int dy[] = { 0, 1, 0, -1 }; // Возможные направления движения по y
    int** dist = new int* [m]; // Матрица расстояний
    for (int i = 0; i < m; i++) {
        dist[i] = new int[n];
        for (int j = 0; j < n; j++)
            dist[i][j] = INT_MAX; // Инициализация матрицы расстояний
    }
    dist[sx][sy] = 0; // Расстояние от начальной точки до себя равно 0
    enqueue(&head, &tail, sx, sy); // Добавление начальной точки в очередь
    while (head != NULL) { // Пока очередь не пуста
        int x = head->x, y = head->y; // Извлечение текущей точки
        dequeue(&head, &tail); // Удаление текущей точки из очереди
        for (int i = 0; i < 4; i++) { // Проверка всех возможных направлений
            int newX = x + dx[i], newY = y + dy[i]; // Новая точка
            // Если новая точка допустима и ближе, чем текущее расстояние
            if (isValid(newX, newY, m, n) && maze[newX][newY] == 0 && dist[newX][newY] > dist[x][y] + 1) {
                dist[newX][newY] = dist[x][y] + 1; // Обновление расстояния
                enqueue(&head, &tail, newX, newY); // Добавление новой точки в очередь
            }
        }
    }
    // Поиск минимального расстояния до края лабиринта
    int minDist = INT_MAX;
    for (int i = 0; i < m; i++) {
        minDist = std::min(minDist, dist[i][0]);
        minDist = std::min(minDist, dist[i][n - 1]);
    }
    for (int i = 0; i < n; i++) {
        minDist = std::min(minDist, dist[0][i]);
        minDist = std::min(minDist, dist[m - 1][i]);
    }
    return (minDist == INT_MAX) ? -1 : minDist; // Возвращение минимального расстояния
}

int main() {
    // Определение лабиринта
    int m = 5, n = 5;
    int** maze = new int* [m];
    for (int i = 0; i < m; i++) {
        maze[i] = new int[n];
    }
    maze[0][0] = 1; maze[0][1] = 1; maze[0][2] = 1; maze[0][3] = 1; maze[0][4] = 1;
    maze[1][0] = 1; maze[1][1] = 1; maze[1][2] = 0; maze[1][3] = 0; maze[1][4] = 1;
    maze[2][0] = 1; maze[2][1] = 1; maze[2][2] = 1; maze[2][3] = 0; maze[2][4] = 1;
    maze[3][0] = 1; maze[3][1] = 1; maze[3][2] = 1; maze[3][3] = 0; maze[3][4] = 1;
    maze[4][0] = 1; maze[4][1] = 1; maze[4][2] = 1; maze[4][3] = 0; maze[4][4] = 0;
    // Вызов функции для поиска кратчайшего пути
    int shortest_distance = shortestPath(maze, 1, 2, m, n);
    // Вывод кратчайшего пути
    std::cout << "The shortest path is " << shortest_distance << std::endl;
    return 0;
}
