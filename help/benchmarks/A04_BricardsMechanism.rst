
MBS Benchmark A04: Bricard's Mechanism
======================================

Benchmark Objective
-------------------
Bricard's mechanism (benchmark problem **A04**) :cite:`1897:bricard` is an example of over-constrained system.
Grübler's formula :cite:`1884:grubler` results in no degrees of freedom, however, the particular orientation of the revolute pairs results in a system with one degree of freedom.

Benchmark Description
---------------------

The system is composed of five rods with square cross section and six revolute joints. Gravity is acting towards the negative y direction.

.. figure:: ../images/4MBS_Bricard.png
   :align: center
   :height: 250pt
   :alt: Bricard
   :figclass: align-center

The following table reports system properties.

.. _systemproperties04:

.. table:: **System Properties and Configuration**

    ============================ ============
     Rods mass                    1.0 kg
     Rods length                  1.0 m
     Square cross section length  0.1 m
    ============================ ============

Results
-------

The dynamic simulation of the **A04** benchmark was executed for 10 s. The previous figure shows the Bricard's Mechanism in its initial position.

Simulation evaluation has been conducted taking into account the total mechanical energy variation from the initial condition.
Total mechanical energy defined as the sum of the kinetic and potential energy of the mechanism.
Since no friction or dissipative elements are present in the mechanism energy should be conserved therefore theoretical value for the mechanical energy variation is zero.

.. figure:: ../images/A04_energy.png
   :align: center
   :height: 300pt
   :alt: A04 energy.
   :figclass: align-center

   Mechanical energy variation during simulation period from the initial condition. Theoretical variation (black line) and simulated one (blue line).


Next figure shows instead :math:`P_3` point displacements estimated with the OpenSim simulation compared with the values provided as reference :cite:`2006:gonzales`.

.. figure:: ../images/A04_kinematics.png
   :align: center
   :height: 300pt
   :alt: A04 kinematics.
   :figclass: align-center

   Comparison of the point :math:`P_3` displacement between Andrew's mechanism model simulated in OpenSim (colored lines) and MBS benchmark reference values (black dashed lines).

Computational Performances
~~~~~~~~~~~~~~~~~~~~~~~~~~
To compute the simulation the developed implementation required 0.258 seconds.

Results obtained using an Intel Core i5-4570 @ 3.2 GHz computer running Windows 8.1 64-bit.
OpenSim official release used: 3.2.

Videos
------

.. only:: html

    .. youtube:: http://www.youtube.com/watch?v=vBpZ6P5VigA

.. only:: latex

  Video of the problem simulated in OpenSim is available at https://youtu.be/vBpZ6P5VigA

Download
--------

* Bricard's mechanism on MBS Benchmark library available at: http://goo.gl/9XLSME
* OpenSim implementation available at: http://goo.gl/R9tl3z
* Video of Bricard's mechanism sumulated in OpenSim available at: https://youtu.be/vBpZ6P5VigA
