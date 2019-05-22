.. .............................................................................
..
..  This file is part of the CMakeDoxyXML toolkit.
..
..  CMakeDoxyXML is distributed under the MIT license.
..  For details see accompanying license.txt file,
..  the public copy of which is also available at:
..  http://tibbo.com/downloads/archive/cmakedoxyxml/license.txt
..
.. .............................................................................

CMakeDoxyXML
==========
.. image:: https://travis-ci.org/vovkos/cmakedoxyxml.svg?branch=master
	:target: https://travis-ci.org/vovkos/cmakedoxyxml
.. image:: https://ci.appveyor.com/api/projects/status/sldqdlltvcbmht7b?svg=true
	:target: https://ci.appveyor.com/project/vovkos/cmakedoxyxml

Abstract
--------

CMakeDoxyXML is a tool for extracting `Doxygen <http://www.stack.nl/~dimitri/doxygen/>`_-style comments from **CMake** source files and outputting those as **Doxygen XML**.

It is indended to be used at the first stage (front-end) in the `Doxyrest pipeline <https://github.com/vovkos/doxyrest>`_ for generating beautiful `Sphinx <http://www.sphinx-doc.org>`_-based documentation for CMake libraries and setting files.

Quick HOWTO
-----------

There are two modes of operation for CMakeDoxyXML.

Direct mode
~~~~~~~~~~~

In this mode, ``cmakedoxyxml`` parses one or more CMake files specified via the command-line and generates Doxygen XML database files directly.

.. rubric:: Example

.. code:: none

	$ cmakedoxyxml -o xml/index.xml settings.cmake macros.cmake

This will generate an XML database out of doxy-comments in ``settings.cmake`` and ``macros.cmake`` and place the resulting XML files into the ``xml/`` subdirectory.

Please note, that in *direct mode* only a small subset of Doxygen `special commands <http://www.doxygen.nl/manual/commands.html>`__ is supported:

* ``\var``
* ``\fn``
* ``\defgroup`` = ``\addtogroup``
* ``\ingroup``
* ``\title``
* ``\brief``
* ``\details``
* ``\param``
* ``\return`` = ``\returns`` = ``\result``
* ``\see`` = ``\sa``

If you use **reStructuredText** inside doxy-comments, you don't really need any of the Doxygen formatting commands -- in this case the *direct mode* is the right choice. However, if you *do need* advanced Doxygen commands, then you can use Doxygen as the main processor and ``cmakedoxyxml`` as a *filter* as described in the next session.

Doxygen filter mode
~~~~~~~~~~~~~~~~~~~

In this mode, ``cmakedoxyxml`` is used to pre-process ``.cmake`` files and output *pseudo-C* declarations and comments which are then handled by Doxygen. The resulting Doxygen XML database will be emitted by Doxygen, and Doxy-comments will be parsed by Doxygen, too -- which means *ALL* Doxygen `special commands <http://www.doxygen.nl/manual/commands.html>`__ will be supported.

To activate this mode, pass ``--doxygen-filter`` via the command-line.

Please note that it's not necessary to do this pre-processing manually for each ``.cmake`` file in your project. ``Doxyfile`` has a setting called ``FILTER_PATTERNS`` which allows for automatic invokation of user-defined pre-processors for all or some source files. To make this work for CMake files, your ``Doxyfile`` should contain the following:

.. code:: bash

	# scan the project directory for CMake files
	FILE_PATTERNS = *.cmake

	# cmakedoxyxml outputs C-alike code
	EXTENSION_MAPPING = cmake=C

	# ... or specify files directly
	INPUT = main.cmake utils.cmake

	# for each CMake file, invoke cmakedoxyxml
	FILTER_PATTERNS = *.cmake="<path-to-cmakedoxyxml> --doxygen-filter"

	# specify how and where to emit XML
	GENERATE_XML = YES
	XML_PROGRAMLISTING = NO
	XML_OUTPUT = <doxygen-xml-dir>

When ``Doxyfile`` is prepared, just invoke Doxygen:

.. code:: none

	$ doxygen Doxyfile

This will generate XML database which can then be used in the usual Doxyrest pipeline.

Generating HTML from XML
~~~~~~~~~~~~~~~~~~~~~~~~

Once you have generated a Doxygen XML database, you can use it to build beautiful HTML documentation out of it using Doxyrest and Sphinx.

.. code:: none

	$ doxyrest \
		<doxygen-xml-dir>/index.xml \
		-o <doxyrest-rst-dir>/index.rst \
		-f index.rst.in \
		-F <path-to-doxyrest-frame-dir>/cmake \
		-F <path-to-doxyrest-frame-dir>/common

	$ sphinx-quickstart

	$ sphinx-build \
		-b html \
		<doxyrest-rst-dir> \
		<final-html-dir>
