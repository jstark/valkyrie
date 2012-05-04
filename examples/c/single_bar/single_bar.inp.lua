material { id = 1, E = 2.1e11 } 
property { id = 1, material = 1, A = 0.1 }

node { id = 1, x = 0.0, y = 0.0 } 
node { id = 2, x = 1.0, y = 0.0 }

element { id = 1, property = 1, nodes = { 1, 2 } }

spc { id = 1, node = 1, dofs = constrained_at(x, y) }
spc { id = 2, node = 2, dofs = constrained_at(y) }

force { id = 1, node = 2, magn = 51.0, direction_components = { 1, 0, 0} }

static_analysis { action = print_results } 
