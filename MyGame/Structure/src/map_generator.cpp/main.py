import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
from map_generator import GameMap

def init_opengl(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0, width, height, 0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def draw_tile(x, y, size, color):
    glBegin(GL_QUADS)
    glColor3fv(color)
    glVertex2f(x, y)
    glVertex2f(x + size, y)
    glVertex2f(x + size, y + size)
    glVertex2f(x, y + size)
    glEnd()

def draw_map(game_map):
    tile_size = 10  # Adjust this value to change the size of each tile
    for y, row in enumerate(game_map.grid):
        for x, tile in enumerate(row):
            if tile.type == 'M':
                color = (0, 0, 1)  # Blue for sea
            elif tile.type == 'P':
                color = (1, 1, 0)  # Yellow for beach
            elif tile.type == 'F':
                color = (0.5, 0.5, 0.5)  # Gray for cliff
            elif tile.type == 'R':
                color = (0.5, 0.25, 0)  # Brown for road
            elif tile.type == 'V':
                color = (0, 0.8, 0)  # Green for village
            elif tile.type == 'I':
                color = (1, 0, 0)  # Red for city
            elif tile.type == 'A':
                color = (1, 0.5, 0)  # Orange for farm
            elif tile.type == 'C':
                color = (0.5, 1, 0.5)  # Light green for field
            elif tile.type == 'B':
                color = (0.5, 0, 0.5)  # Purple for military base
            elif tile.type == 'T':
                color = (0, 0, 0)  # Black for fortification
            else:
                color = (1, 1, 1)  # White for unknown
            
            draw_tile(x * tile_size, y * tile_size, tile_size, color)

def main():
    pygame.init()
    width, height = 5000, 2000
    screen = pygame.display.set_mode((width, height), pygame.OPENGL | pygame.DOUBLEBUF)
    clock = pygame.time.Clock()

    init_opengl(width, height)

    # Création de la carte (taille réduite pour l'exemple)
    game_map = GameMap(80, 60)
    game_map.generate_map()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        draw_map(game_map)

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()