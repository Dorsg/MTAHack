import pygame
import config
import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 3000        # The port used by the server

class Player:
    def __init__(self, x_postition, y_position):
        print("player created")
        self.position = [x_postition, y_position]
        self.image = pygame.image.load("imgs/player.png")
        self.image = pygame.transform.scale(self.image, (config.SCALE , config.SCALE ))
        self.rect = pygame.Rect(self.position[0] * config.SCALE, self.position[1] * config.SCALE, config.SCALE, config.SCALE)

    def update(self):
        print("player updated")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            s.send(self.position)
            data = s.recv(1024)

        print('Received', repr(data))


    def update_position(self, new_position):
        self.position[0] = new_position[0]
        self.position[1] = new_position[1]


    def render(self, screen, camera):
        self.rect = pygame.Rect(self.position[0] * config.SCALE, self.position[1] * config.SCALE - (camera[1] * config.SCALE), config.SCALE, config.SCALE)
        screen.blit(self.image, self.rect)
