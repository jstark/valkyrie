material { id = 1, E = 30e6 }
property { id = 1, A = 2, material = 1 }

node { id = 1, x = 0, y = 0, z = 0 }
node { id = 2, x = 0, y =10, z = 0 }
node { id = 3, x =10, y =10, z = 0 }
node { id = 4, x =10, y = 0, z = 0 }

element { id = 1, property = 1, nodes = { 1, 2 } }
element { id = 2, property = 1, nodes = { 1, 3 } }
element { id = 3, property = 1, nodes = { 1, 4 } }

spc { id = 1, dofs = constrained_at(x, y), node = 2 }
spc { id = 2, dofs = constrained_at(x, y), node = 3 }
spc { id = 3, dofs = constrained_at(x, y), node = 4 }

force { id = 1, magn = 10000, direction_components = { 0, -1, 0 }, node = 1 }

static_analysis { action = print_results }
