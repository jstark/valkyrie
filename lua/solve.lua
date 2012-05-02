require 'valkyrie'

model = {}
model.id = 1;

model.create_material = function (t)
    local matid = t.id or error('material id missing')
    local E = t.E  or 2.1e11
    local r = t.rho or 7800.0
    local name = t.name or ''
    valkyrie.create_material(model.id, matid, E, r, name)
end

model.create_property = function (t)
    local propid = t.id or error('property id missing')
    local matid  = t.material or error('material id missing')
    local A = t.A or error('property cross-section missing')
    local name = t.name or ''
    valkyrie.create_property(model.id, propid, matid, A, name);
end

model.create_node = function (t)
    local nodeid = t.id or error ('node id missing')
    local x = t.x or 0.0
    local y = t.y or 0.0
    local z = t.z or 0.0
    valkyrie.create_node(model.id, nodeid, x, y, z)
end

model.create_rod = function (t)
    local rodid = t.id or error('element id missing')
    local pid = t.property or error('property id missing')
    local nodes = t.nodes or error('nodes missing')

    if #nodes ~= 2 then error('number of node ids not equal to 2') end
    if type(nodes[1]) ~= type(0) or type(nodes[2]) ~= type(0) then
        error('nodes are given as integers')
    end
    valkyrie.create_element(model.id, rodid, pid, nodes[1], nodes[2])
end

model.x = 1
model.y = 2
model.z = 3

model.constrained_at = function (...)
    local args = {...}
    if #args > 3 then error('up to three constraints can be specified') end
    c = {}
    for i = 1, #args do
        c[i] = 1;
    end
    return function (dof)
        return c[dof] or 0
    end
end

model.create_spc = function (t)
    local spcid = t.id or error('spc id missing')
    local constr= t.dofs or error('constrained dofs missing')
    if type(constr) ~= type(model.create_rod) then
        error('invalid spc formulation, check dofs')
    end
    local nid = t.node or error('constrained node missing')
    valkyrie.create_spc(model.id, t.id, valkyrie.constraint_code(constr(x), constr(y), constr(z)), nid)
end

model.create_force = function (t)
    local fid = t.id or error('force id missing')
    local nid = t.node or error('node to apply force missing')
    local mag = t.magn or error('force magnitude missing')
    local dir = t.direction_components or error('direction components missing')
    
    if type(dir) ~= type({}) then error('invalid direction components') end
    if #dir ~= 3 then error('three components must be given') end

    valkyrie.create_force(model.id, fid, nid, mag, dir[1], dir[2], dir[3]) 
end

model.print_results = function (id)
    valkyrie.print_results(id)
end

model.static_analysis = function (t)
    valkyrie.perform_static_analysis(model.id)
    
    local action = t.action or print_results
    action(model.id)
end

material = model.create_material
property = model.create_property
node = model.create_node
element = model.create_rod
constrained_at = model.constrained_at
spc = model.create_spc
force = model.create_force
static_analysis = model.static_analysis
print_results = model.print_results

x = model.x
y = model.y
z = model.z

valkyrie.create_model(model.id)

if #arg ~= 1 then 
    print('usage: lua solve.lua "input file"') 
else
    dofile(arg[1])
end
