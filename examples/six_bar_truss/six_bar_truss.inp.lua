-- define materials
material { id = 1, name = 'wood', E = 1.9e06 }

-- define properties
-- (materials must be already defined)
property { id = 1, name = 'wood-property', A = 8.0, material = 1 }

-- define nodes
node { id = 1, x =  0.0, y =  0.0 }
node { id = 2, x = 36.0, y =  0.0 }
node { id = 3, x =  0.0, y = 36.0 }
node { id = 4, x = 36.0, y = 36.0 } 
node { id = 5, x = 72.0, y = 36.0 }

-- define elements. 
-- (nodes and properties must be already defined) 
element { id = 1, property = 1, nodes = { 1, 2 } }
element { id = 2, property = 1, nodes = { 2, 3 } }
element { id = 3, property = 1, nodes = { 3, 4 } }
element { id = 4, property = 1, nodes = { 2, 4 } }
element { id = 5, property = 1, nodes = { 2, 5 } }
element { id = 6, property = 1, nodes = { 4, 5 } }

-- define single point constraints (Spcs)
-- (nodes must be already defined)
spc { id = 1, dofs = constrained_at(x, y), node = 1 };
spc { id = 2, dofs = constrained_at(x, y), node = 3 };

-- forces
-- (nodes must be already defined)
force { id = 1, magn = 500.0, direction_components = { 0, -1, 0}, node = 4 }
force { id = 2, magn = 500.0, direction_components = { 0, -1, 0}, node = 5 } 

-- do a static analysis
static_analysis { action = print_results }

