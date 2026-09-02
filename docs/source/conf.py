# -*- coding: utf-8 -*-

'''
Module
    conf.py
Copyright
    Copyright (C) 2020 - 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
    microhil is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    microhil is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    Defines properties for sphinx-doc.
'''

from os.path import abspath
from sys import path

path.insert(0, abspath('../../'))

project: str = 'microhil'
project_copyright: str = '2017, https://vroncevic.github.io/microhil'
author: str = 'Vladimir Roncevic <elektron.ronca@gmail.com>'
version: str = '1.0.0'
release: str = 'https://github.com/vroncevic/microhil/releases'
extensions: list[str] = ['sphinx.ext.autodoc', 'sphinx.ext.viewcode', ]
templates_path: list[str] = ['_templates']
source_suffix: str = '.rst'
master_doc: str = 'index'
language: str = 'en'
html_static_path = ['_static']
exclude_patterns: list[str] = []
pygments_style: str = 'sphinx'
html_theme: str = 'classic'
html_static_path: list[str] = ['_static']
htmlhelp_basename: str = 'microhildoc'
latex_elements: dict[object, object] = {}
latex_documents: list[tuple[object, ...]] = [(
    master_doc, 'microhil.tex', 'ats\\_utilities Documentation',
    'Vladimir Roncevic \\textless{}elektron.ronca@gmail.com\\textgreater{}',
    'manual'
)]
man_pages: list[tuple[object, ...]] = [(
    master_doc, 'microhil', 'microhil Documentation', [author], 1
)]
texinfo_documents: list[tuple[object, ...]] = [(
    master_doc, 'microhil', 'microhil Documentation',
    author, 'microhil', 'One line description of project.',
    'Miscellaneous'
)]
epub_title: str = project
epub_exclude_files: list[str] = ['search.html']
