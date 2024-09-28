#include <vector>
#include <string>
#include <random>
#include <iostream>

class Zone {
public:
    char type;
    Zone(char t) : type(t) {}
};

class GameMap {
private:
    int width, height;
    std::vector<std::vector<Zone>> grid;
    std::mt19937 rng;

public:
    GameMap(int w, int h) : width(w), height(h), rng(std::random_device{}()) {
        grid.resize(height, std::vector<Zone>(width, Zone('X')));
        generateMap();
    }

    void generateMap() {
        generateCoast();
        fillMap();
        addRoads();
    }

    void generateCoast() {
        for (int y = 0; y < height; ++y) {
            grid[y][0].type = 'M';
            grid[y][1].type = 'M';
            int beachWidth = std::uniform_int_distribution<>(2, 4)(rng);
            for (int x = 2; x < 2 + beachWidth && x < width; ++x) {
                grid[y][x].type = 'P';
            }
            if (2 + beachWidth < width) {
                grid[y][2 + beachWidth].type = 'F';
            }
        }

        for (int y = 0; y < height; y += 6) {
            int passageY = std::uniform_int_distribution<>(y, std::min(y + 5, height - 1))(rng);
            for (int x = 0; x < width; ++x) {
                if (grid[passageY][x].type == 'F') {
                    grid[passageY][x].type = 'P';
                    break;
                }
            }
        }
    }

    void fillMap() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].type == 'X') {
                    char zoneType = chooseZoneType(x, y);
                    placeZoneCluster(x, y, zoneType);
                }
            }
        }
        placeFortifications();
    }

    char chooseZoneType(int x, int y) {
        if (isNearCliff(x, y)) {
            return std::uniform_int_distribution<>(0, 1)(rng) ? 'F' : 'T';
        }
        static const char types[] = {'F', 'C', 'V', 'I', 'A', 'B'};
        return types[std::uniform_int_distribution<>(0, 5)(rng)];
    }

    bool isNearCliff(int x, int y) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (grid[ny][nx].type == 'F') return true;
                }
            }
        }
        return false;
    }

    void placeZoneCluster(int x, int y, char zoneType) {
        int size;
        switch (zoneType) {
            case 'F': size = std::uniform_int_distribution<>(6, 20)(rng); break;
            case 'V': size = std::uniform_int_distribution<>(4, 6)(rng); break;
            case 'I': size = std::uniform_int_distribution<>(7, 10)(rng); break;
            case 'C': size = std::uniform_int_distribution<>(25, 100)(rng); break;
            case 'B': size = 16; break;
            case 'T': size = 4; break;
            case 'A': placeFarm(x, y); return;
            default: return;
        }

        int placed = 0;
        for (int dy = -5; dy <= 5 && placed < size; ++dy) {
            for (int dx = -5; dx <= 5 && placed < size; ++dx) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx].type == 'X') {
                    grid[ny][nx].type = zoneType;
                    ++placed;
                }
            }
        }
    }

    void placeFarm(int x, int y) {
        if (x + 3 < width && y + 3 < height) {
            for (int dy = 0; dy < 4; ++dy) {
                for (int dx = 0; dx < 4; ++dx) {
                    if (grid[y+dy][x+dx].type == 'X') {
                        grid[y+dy][x+dx].type = 'A';
                    }
                }
            }
            
            for (int dy = -5; dy < 9; ++dy) {
                for (int dx = -5; dx < 9; ++dx) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx].type == 'X') {
                        placeZoneCluster(nx, ny, 'C');
                        return;
                    }
                }
            }
        }
    }

    void placeFortifications() {
        for (int y = 0; y < height; ++y) {
            int lastFortification = -7;
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].type == 'F' && x - lastFortification >= 7) {
                    if (placeFortificationNearCliff(x, y)) {
                        lastFortification = x;
                    }
                }
            }
        }
    }

    bool placeFortificationNearCliff(int x, int y) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < width - 1 && ny >= 0 && ny < height - 1) {
                    if (grid[ny][nx].type == 'X' && grid[ny][nx+1].type == 'X' &&
                        grid[ny+1][nx].type == 'X' && grid[ny+1][nx+1].type == 'X') {
                        grid[ny][nx].type = grid[ny][nx+1].type = 
                        grid[ny+1][nx].type = grid[ny+1][nx+1].type = 'T';
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void addRoads() {
        // Simplified road generation
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].type == 'V' || grid[y][x].type == 'I' || 
                    grid[y][x].type == 'A' || grid[y][x].type == 'B') {
                    connectToNearestRoad(x, y);
                }
            }
        }
    }

    void connectToNearestRoad(int x, int y) {
        for (int r = 1; r < std::max(width, height); ++r) {
            for (int dy = -r; dy <= r; ++dy) {
                for (int dx = -r; dx <= r; ++dx) {
                    if (std::abs(dx) == r || std::abs(dy) == r) {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            if (grid[ny][nx].type == 'R') {
                                drawRoad(x, y, nx, ny);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    void drawRoad(int x1, int y1, int x2, int y2) {
        int dx = (x2 > x1) ? 1 : (x2 < x1) ? -1 : 0;
        int dy = (y2 > y1) ? 1 : (y2 < y1) ? -1 : 0;

        int x = x1, y = y1;
        while (x != x2 || y != y2) {
            if (grid[y][x].type == 'X') {
                grid[y][x].type = 'R';
            }
            if (std::abs(x - x2) > std::abs(y - y2)) {
                x += dx;
            } else {
                y += dy;
            }
        }
    }

    void displayMap() {
        for (const auto& row : grid) {
            for (const auto& zone : row) {
                std::cout << zone.type << ' ';
            }
            std::cout << std::endl;
        }
    }
};