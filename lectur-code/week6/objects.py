#!/usr/bin/env python3

class Dog():

    def __init__(self, name, age, color):
        self.name = name
        self.age = age
        self.color = color

    def print(self):
        print(f"{self.name} - {self.age} - {self.color}")

mina = Dog("Mina", 3, "Yellow")
gau = Dog("Gau", 2, "Brown")
gau.print()
# jane.changeID(2555)
# jane.print()