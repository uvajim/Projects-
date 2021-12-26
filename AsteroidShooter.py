#Name: Jim Liang
#NETID: jl7ut
#Desc: Final Project: gamebox

"""
How to Play:

The goal is to survive for as long as possible and to try and score as many points as you can. The game progressively
more difficult like the fitness grand pacer test every minute. By difficult, asteroids will spawn in faster and faster.

How To Score Points:

Eliminating enemies: Each asteroid elininated is a point

Surviving: Every minute survived is worth ten points and every second is worth a point.

Collectibles: Collect the upgrade tokens! They are worth 10 points each in addition to upgrading your lasers and ship speed!

Controls:

WASD for movement and spacebar for firing lasers.

How do I lose?

When an asteroid either crosses the bottom of the screen or if you are touched by one.
"""

import pygame
import gamebox
import random

width = 800
height = 600
score = 0
counter = 0
counter_speed = 1
Alive = True
death_speed = 2
timer = 0
seconds = 0
minutes = 0
speed = 5
difficulty = 150

camera = gamebox.Camera(width, height)
player = gamebox.from_image(400, 500, "http://www.cs.virginia.edu/~up3f/cs1111/images/spaceship.jpg")

player_lasers = []

collectibles = []

enemies = [ gamebox.from_image(500, 100, 'https://opengameart.org/sites/default/files/styles/medium/public/Asteroid%20Brown.png')
           ]
def tick(keys):
    global player_lasers, score, counter, Alive, timer, seconds, minutes, lives, death_speed, counter_speed, collectibles, enemies, speed, difficulty
    camera.clear('black')
    camera.draw(player)

    timer += counter_speed

    if timer % 30 == 0:
        seconds += 1
        if seconds % 60 == 0:
            seconds = 0
            minutes += 1


    if minutes == 1:
        difficulty = 120
    if minutes == 2:
        difficulty = 90
    if minutes == 3:
        difficulty = 60
    if minutes > 3:
        difficulty = 30




    if seconds < 10:
        time = str(minutes) + ':' + '0' + str(seconds)
    if seconds >= 10:
        time = str(minutes) + ':' + str(seconds)



    scoreboard = gamebox.from_text(50, camera.y + 250, str(score), 70, "red")
    time_alive = gamebox.from_text(700, camera.y + 250, time, 70, "red")
    camera.draw(time_alive)
    camera.draw(scoreboard)




        
    for lasers in player_lasers:  # player firing system
        camera.draw(lasers)
        if lasers.y < 0:
            player_lasers.remove(lasers)
        lasers.y -= speed

    if timer % difficulty == 0:
        new_enemy = gamebox.from_image(random.randint(0, 800), -100,
                                       'https://opengameart.org/sites/default/files/styles/medium/public/Asteroid%20Brown.png')
        enemies.append((new_enemy))

    for opponents in enemies:

        camera.draw(opponents)
        opponents.y += death_speed
        if opponents.y > height or opponents.touches(player):
            Alive = False
            death_speed = 0
            counter_speed = 0
            camera.draw(gamebox.from_text(400, 150, "GAME OVER", 70, "red"))
            camera.draw(
            gamebox.from_text(400, 500, 'You survived for ' + str(time) + ' and scored ' + str(score + (minutes  * 10) + (seconds * 1)) + ' points',50, 'red'))
        for lasers in player_lasers:
            if lasers.y < 0:
                player_lasers.remove(lasers)
            if lasers.touches(opponents):
                score += 1
                enemies.remove(opponents)
                player_lasers.remove(lasers)
    if timer % random.randint(150, 450) == 0 and collectibles ==[]:
        new_coin = gamebox.from_circle(random.randint(150,650), random.randint(150,500), 'yellow', 5)
        collectibles.append(new_coin)

    for coin in collectibles:
        camera.draw(coin)
        if player.touches(coin):
            speed += 1
            score += 10
            collectibles = []

    if pygame.K_d in keys:  # movement
        player.x += speed
    if pygame.K_a in keys:
        player.x -= speed
    if pygame.K_SPACE in keys:
        new_laser = gamebox.from_color(player.x, player.y, 'yellow', 10, 20)
        player_lasers.append(new_laser)
    if pygame.K_s in keys:
        player.y += speed
    if pygame.K_w in keys:
        player.y -= speed

    camera.display()



gamebox.timer_loop(30, tick)