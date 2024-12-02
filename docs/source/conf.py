# Configuration file for the Sphinx documentation builder.

import os
import sys

# -- Project information -----------------------------------------------------
project = "SPARSE_MATRIX"
author = "Jorge,Luis,Gloria,Massimo"
copyright = "2024, Jorge"

# -- General configuration ---------------------------------------------------
extensions = [
    "breathe",
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
]

# Breathe Configuration
breathe_projects = {
    project: os.path.join("..", "build", "doxygen", "xml")
}
breathe_default_project = project
breathe_default_members = ("members", "undoc-members")

templates_path = ["_templates"]
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
html_theme = "alabaster"
html_static_path = ["_static"]

# Adding to this variable allows to pass variables to the ReST files.
rst_epilog = """
.. |project| replace:: {}
""".format(project)