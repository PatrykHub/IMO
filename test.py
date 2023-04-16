import pytest 
from zad2 import * 

def test_change_edge():
    assert (change_edge(np.array([0,1,2,3]), 0, 3) == np.array([0,2,1,3])).all()


def test_count_delta_for_swap_edges():
    dis_ma = np.array([0,1,2,3,1,0,4,5,2,4,0,6,3,5,6,0]).reshape((4,4))
    assert count_delta_for_swap_edges(np.array([0,1,2,3]), 0, 3, dis_ma) == 0



