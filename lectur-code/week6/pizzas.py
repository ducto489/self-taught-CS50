pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12
}

pizzas["cream"] = 30

for pie in pizzas:
    cost = pizzas[pie]
    print(f"A whole {pie} pizza costs ${cost}")