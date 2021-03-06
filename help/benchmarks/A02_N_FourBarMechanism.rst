
MBS Benchmark A02: N-Four-Bar Mechanism
=======================================

Benchmark Objective
-------------------
The **A02** MBS benchmark problem is a common example of a mechanism which undergoes singular configuration.

Benchmark Description
---------------------
The N-four-bar mechanism is a common example of a mechanism which undergoes singular configuration.
The system has N four-bar windows composed of 2N+1 links. It is an extension of the two four-bar mechanism proposed in :cite:`1994:bayo`.
When the mechanism reaches the horizontal position, the number of the degrees of freedom instantaneously increase from 1 to N+1.
Gravity acts on the negative y direction.


.. figure:: ../images/2MBS_N-FourBar.png
   :align: center
   :height: 200pt
   :alt: N-four-bar mechanism sketch.
   :figclass: align-center


The following table reports the initial configuration of the system.

+--------------------------+--------------------------------+
|         **System Properties and Configuration**           |
+==========================+================================+
| N                        |    2                           |
+--------------------------+--------------------------------+
| Link mass                |    1.0 Kg                      |
+--------------------------+--------------------------------+
| Link length              |    1.0 m                       |
+--------------------------+--------------------------------+
| :math:`\dot{B_{0}x}(0)`  |    1.0 m/s                     |
+--------------------------+--------------------------------+


Results
-------
The dynamic simulation of the **A02** benchmark was executed for a period of 10 seconds.
The starting position of the simulation is shown in the previous picture with an initial speed for the point :math:`B_0` in the positive x-direction of 1 m/s.

The accuracy of the simulation has been measured as the variation in the mechanical energy from the initial condition. Mechanical energy defined as the sum of potential and kinetic energy. Since no dissipation phenomena is included in problem definition, theoretical value for mechanical energy variation shoud be zero.

Additional evaluation has been conducted comparing the simulated displacement of the point :math:`B_0`, with the reference solution provided by the problem authors :cite:`2006:gonzales`.

The simulation with OpenSim perfectly matches the reference values.

.. figure:: ../images/A02_energy.png
   :align: center
   :height: 300pt
   :alt: A02 energy.
   :figclass: align-center

   Mechanical energy variation during simulation period from the initial condition. Theoretical variation (black line) and simulated one (blue line).


.. figure:: ../images/A02_kinematics.png
   :align: center
   :height: 300pt
   :alt: A02 kinematics.
   :figclass: align-center

   Displacement of reference point :math:`B_0` in OpenSim simulation (colored lines) and MBS benchmark reference (black dashed lines).

Computational Performances
~~~~~~~~~~~~~~~~~~~~~~~~~~
To compute the simulation the developed implementation required 0.455 seconds.

Results obtained using an Intel Core i5-4570 @ 3.2 GHz computer running Windows 8.1 64-bit.
OpenSim official release used: 3.2.

Comparision with other dynamic engines has been conducted submitting the obtained results to the benchmark collaborative library.
Click `here <http://goo.gl/c50tLg>`_ to see the comparison results.

Videos
------
.. only:: html

    .. youtube:: eSesPhGIhco

.. only:: latex

  Video of the problem simulated in OpenSim is available at https://youtu.be/eSesPhGIhco

Download
--------

* N-four-bar mechanism on MBS Benchmark library available at: http://goo.gl/c50tLg
* OpenSim implementation available at: http://goo.gl/R9tl3z
* Video of N-four-bar mechanism simulated in OpenSimn available at: https://youtu.be/eSesPhGIhco
