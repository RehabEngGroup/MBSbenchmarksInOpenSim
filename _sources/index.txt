.. title:: MBS Benchmarks in OpenSim  Reference Documentation


Multi-Body Systems Benchmark in OpenSim (MBS-BOS)
*************************

.. only:: html or latex

   .. contents::

##############
MBS-BOS
##############

MBS-BOS package is a set of programs that implement the Multi-Body Systems (MBS) Benchmark :cite:`2006:gonzales` using the OpenSim :cite:`2007:opensim` APIs.

The first objective is to assess OpenSim performances in simulating mechanical and robotic devices both in terms of accuracy and solving time.

The second objective is to provide C++ solutions for common problems that can be found in the implementation of simulations of multi-body systems.

If you use MBS-BOS for research work, please cite:

``L. Tagliapietra, M. Vivian, R. Caracciolo, and M. Reggiani. Evaluation of the biomechanical simulator OpenSim on a multi-body system benchmark. In Proceedings of the 2015 ECCOMAS Thematic Conference on Multibody Dynamics, Barcelona, July 2015 (2015)``

##############
Latest Version
##############
MBS-BOS is an open project, released under GNU General Public License and hosted in GitHub:

https://github.com/RehabEngGroup/MBSbenchmarksInOpenSim

A PDF version of this documentation can be found also on the SimTK.org page of this project:

https://simtk.org/home/mbs_bos

##################
Benchmark Problems
##################

.. toctree::
   /benchmarks/A01_SimplePendulum
   /benchmarks/A02_N_FourBarMechanism
   /benchmarks/A03_AndrewsMechanism
   /benchmarks/A04_BricardsMechanism
   /benchmarks/A05_FlyballGovernor
   zreferences

#################
Acknowledgements
#################

MBS Benchmarks in Opensim have been developed by the `Rehabilitation Engineering Group`_, `Dipartimento di Tecnica e Gestione dei Sistemi Industriali`_,
`Universita' degli Studi di Padova`_.

.. only:: html

    .. list-table::

        * - .. image:: images/reglogo.png
              :height: 100pt
              :alt: DTG logo
              :target: `Rehabilitation Engineering Group`_
          - .. image:: images/unipd.png
              :height: 100pt
              :alt: UNIPD logo
              :target: `Universita' degli Studi di Padova`_


.. only:: latex

    .. list-table::

        * - .. image:: images/reglogo.png
              :height: 100pt
              :alt: DTG logo
          - .. image:: images/unipd.png
              :height: 100pt
              :alt: UNIPD logo

Luca Tagliapietra, Michele Vivian, Monica Reggiani, and Elena Ceseracciu acknowledge the financial support of the ICT
programme within the Seventh Framework Programme for Research of the
European Commission (`BioMot`_ project, grant number: 611695).


.. image:: images/biomot.png
   :height: 100pt
   :align: center
   :alt: BioMot logo
   :target: `BioMot`_

.. only:: html

 Index and Search
 ################

 * :ref:`search`
.. * :ref:`genindex`
