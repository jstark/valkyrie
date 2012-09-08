#!/usr/bin/env python3

import argparse
import turtle
from pyvalkyrie import *

"""
Usage: python3 pyvalkyrie.py --m file_path

version: v1.1

"""

###############################################################################
class Constants:
    ID = 'id'
    NAME = 'name'
    YOUNG_MODULUS = 'E'
    DENSITY = 'rho'
    PROPERTY_MAT_ID = 'material'
    PROPERTY_AREA = 'A'
    NODE_X = 'x'
    NODE_Y = 'y'
    NODE_Z = 'z'
    ROD_NODES = 'nodes'
    ROD_PROPERTY_ID = 'property'
    SPC_DOFS = 'dofs'
    SPC_NODE_ID = 'node'
    FORCE_NODE_ID = 'node'
    FORCE_MAGNITUDE = 'magn'
    FORCE_DIR = 'dir'
    ANALYSIS_ACTION = 'action'

###############################################################################
class ErrorMessages:
    MATERIAL_ID_MISSING = 'Material Id is mandatory'
    PROPERTY_ID_MISSING = 'Property Id is mandatory'
    PROPERTY_AREA_LEQ_ZERO = 'Property Area must be greater than 0'
    NODE_ID_MISSING = 'Node Id is mandatory'
    ROD_ID_MISSING = 'Rod Id is mandatory'
    ROD_PROPERTY_ID_MISSING = 'Rod Property Id is mandatory'
    ROD_NODE_IDS_MISSING = 'Rod Node Ids are mandatory' 
    SPC_ID_MISSING = 'Spc Id is mandatory'
    SPC_DOFS_MISSING = 'Spc constrained Dofs are mandatory'
    SPC_NODE_ID_MISSING = 'Spc Node Id is mandatory'
    FORCE_ID_MISSING = 'Force Id is mandatory'
    FORCE_NODE_ID_MISSING = 'Force Node Id is mandatory'
    FORCE_DIR_VECTOR_MISSING = 'Force Direction Vector is mandatory'

###############################################################################
class Model:
    ID = 1

###############################################################################

create_model(Model.ID, '__main__')


###############################################################################
def _get_id(d):
    return d.get(Constants.ID, None)

###############################################################################
def _get_material_id(m):
    mid = _get_id(m)
    if mid is None:
        raise Exception(ErrorMessages.MATERIAL_ID_MISSING)
    return mid

###############################################################################
def _get_name(d):
    return d.get(Constants.NAME, None)

###############################################################################
def _get_material_name(m):
    mname = _get_name(m)
    if mname is None:
        mname = ''
    return mname

###############################################################################
def _material(**kwargs):
    """example: material(id=1, E = 2.1e11, rho = 7800, name = 'steel')"""
    material_id = _get_material_id(kwargs)
    material_nm = _get_material_name(kwargs)
    Epsilon = kwargs.get(Constants.YOUNG_MODULUS, 2.1e11)
    Rho = kwargs.get(Constants.DENSITY, 7800.0)
    create_material(Model.ID, material_id, Epsilon, Rho, material_nm)

###############################################################################
def _get_property_name(p):
    mname = _get_name(p)
    if mname is None:
        mname = ''
    return mname

###############################################################################
def _get_property_id(p):
    pid = _get_id(p)
    if pid is None:
        raise Exception(ErrorMessages.PROPERTY_ID_MISSING)
    return pid

###############################################################################
def _get_property_material_id(p):
    mid = p.get(Constants.PROPERTY_MAT_ID, None)
    if mid is None:
        raise Exception(ErrorMessages.PROPERTY_ID_MISSING)
    return mid

###############################################################################
def _get_property_area(p):
    area = p.get(Constants.PROPERTY_AREA, None)
    if area > 0.0:
        return area
    else:
        raise Exception(ErrorMessages.PROPERTY_AREA_LEQ_ZERO)

###############################################################################
def _property(**kwargs):
    property_id = _get_property_id(kwargs)
    material_id = _get_property_material_id(kwargs)
    property_nm = _get_property_name(kwargs)
    Area = _get_property_area(kwargs)
    create_property(Model.ID, property_id, material_id, Area, property_nm)

###############################################################################
def _get_node_id(n):
    node_id = n.get(Constants.ID, None)
    if node_id is None:
        raise Exception(ErrorMessages.NODE_ID_MISSING)
    return node_id

###############################################################################
def _node(**kwargs):
    """example: node(id=1, x = 0.0, y = 0.5)"""
    node_id = _get_node_id(kwargs)
    x = kwargs.get(Constants.NODE_X, 0.0)
    y = kwargs.get(Constants.NODE_Y, 0.0)
    z = kwargs.get(Constants.NODE_Z, 0.0)
    create_node(Model.ID, node_id, (x, y, z))

##############################################################################
def _get_rod_id(n):
    rod_id = _get_id(n)
    if rod_id is None:
        raise Exception(ErrorMessages.ROD_ID_MISSING)
    return rod_id

###############################################################################
def _get_rod_property_id(n):
    pid = n.get(Constants.ROD_PROPERTY_ID, None)
    if pid is None:
        raise Exception(ErrorMessages.ROD_PROPERTY_ID_MISSING)
    return pid

##############################################################################
def _get_rod_node_ids(n):
    node_ids = n.get(Constants.ROD_NODES, None)
    if node_ids is None:
        raise Exception(ErrorMessages.ROD_NODE_IDS_MISSING)
    return node_ids

##############################################################################
def _rod(**kwargs):
    rod_id = _get_rod_id(kwargs)
    rod_pid= _get_rod_property_id(kwargs)
    n1, n2 = _get_rod_node_ids(kwargs)
    create_rod(Model.ID, rod_id, rod_pid, (n1, n2))

##############################################################################
def _get_spc_id(s):
    spc_id = _get_id(s)
    if spc_id is None:
        raise Exception(ErrorMessages.SPC_ID_MISSING)
    return spc_id

##############################################################################
def _get_spc_dofs(s):
    dofs = s.get(Constants.SPC_DOFS, None)
    if dofs is None:
        raise Exception(ErrorMessages.SPC_DOFS_MISSING)
    return dofs

##############################################################################
def _get_spc_node_id(s):
    node_id = s.get(Constants.SPC_NODE_ID, None)
    if node_id is None:
        raise Exception(ErrorMessages.SPC_NODE_ID_MISSING)
    return node_id

##############################################################################
def _spc(**kwargs):
    spc_id = _get_spc_id(kwargs)
    xdof, ydof, zdof = _get_spc_dofs(kwargs)
    node_id= _get_spc_node_id(kwargs)
    create_spc(Model.ID, spc_id, (xdof, ydof, zdof), node_id)

##############################################################################
def _get_force_id(f):
    force_id = _get_id(f)
    if force_id is None:
        raise Exception(ErrorMessages.FORCE_ID_MISSING)
    return force_id

##############################################################################
def _get_force_node_id(f):
    node_id = f.get(Constants.FORCE_NODE_ID, None)
    if node_id is None:
        raise Exception(ErrorMessages.FORCE_NODE_ID_MISSING)
    return node_id

##############################################################################
def _get_force_magnitude(f):
    force_magn = f.get(Constants.FORCE_MAGNITUDE, 0.0)
    return force_magn


##############################################################################
def _get_force_dir(f):
    force_dir = f.get(Constants.FORCE_DIR, None)
    if force_dir is None:
        raise Exception(ErrorMessages.FORCE_DIR_VECTOR_MISSING)
    return force_dir

##############################################################################
def _force(**kwargs):
    force_id = _get_force_id(kwargs)
    force_nid= _get_force_node_id(kwargs)
    magnitude= _get_force_magnitude(kwargs)
    nx, ny, nz = _get_force_dir(kwargs)
    create_force(Model.ID, force_id, force_nid, magnitude, (nx, ny, nz))

##############################################################################
def _print_results(model_id):
    print('NODAL RESULTS:')
    for nr in nodal_results():
        nid, disp, reactions = nr
        print('{id}\t{ux}\t{uy}\t{uz}\t{rx}\t{ry}\t{rz}'.format(id=nid, ux=disp[0], uy=disp[1], uz=disp[2], rx=reactions[0], ry=reactions[1], rz=reactions[2]))

    print('ROD RESULTS:')
    for rr in rod_results():
        rid, res = rr
        stress, strain, reactions = res
        print('{id}\t{s}\t{e}\t{r}'.format(id=rid, s=stress, e=strain, r=reactions))


##############################################################################
def _draw_geometry():
    all_rods = rods()
    all_nodes= nodes()
    for n in all_nodes:
        nid, x, y, z = n
        turtle.setpos(x,y)
        turtle.circle(5)

##############################################################################
def _static_analysis(**kwargs):
    run_static_analysis(Model.ID)
    action = kwargs.get(Constants.ANALYSIS_ACTION, _print_results)
    action(Model.ID)

##############################################################################
#                           GENERATOR FUNCTIONS                              #
##############################################################################
def nodes():
    mnodes = []
    for_each_node(Model.ID, lambda nid, x, y, z : mnodes.append((nid, x, y, z)))
    return mnodes

##############################################################################
def rods():
    mrods = []
    for_each_rod(Model.ID, lambda rid, pid, fn, sn : mrods.append((rid, pid, fn, sn)))
    return mrods

##############################################################################
def spcs():
    mspcs = []
    for_each_spc(Model.ID, lambda sid, nid, dofs : mspcs.append((sid, nid, (dofs[0], dofs[1], dofs[2]))))
    return mspcs

##############################################################################
def forces():
    mforces = []
    for_each_force(Model.ID, lambda fid, magn, ux, uy, uz, nid : mforces.append((fid, magn, (ux, uy, uz), nid)))
    return mforces

##############################################################################
def nodal_results():
    results = []
    for_each_nodal_result(Model.ID, lambda nid, displ, react : results.append((nid, displ, react)))
    return results

##############################################################################
def rod_results():
    results = []
    for_each_rod_result(Model.ID, lambda rid, res : results.append((rid, res)))
    return results

##############################################################################
#                       END OF GENERATOR FUNCTIONS                           #
##############################################################################


###############################################################################

GDICT = {
        'material' : _material,
        'property' : _property,
        'rod'      : _rod,
        'node'     : _node,
        'spc'      : _spc,
        'force'    : _force,
        'static_analysis' : _static_analysis,
        'print_results' : _print_results,
        }

###############################################################################
def run(file):
    global GDICT
    try:
        with open(file, 'r') as file_handle:
            exec(compile(file_handle.read(), file, 'exec'), GDICT)
    except Exception as e:
        raise e

###############################################################################
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--m', metavar='file', help='The model file')

    args = parser.parse_args();
    model_file = args.m
    if model_file is not None:
        run(model_file)


###############################################################################
if __name__ == '__main__':
    main()
