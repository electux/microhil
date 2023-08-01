# -*- coding: utf-8 -*-

project = u'microhil'
copyright = u'2020, Vladimir Roncevic <elektron.ronca@gmail.com>'
author = u'Vladimir Roncevic <elektron.ronca@gmail.com>'
version = u'1.0'
release = u'https://github.com/electux/microhil/releases/'
extensions = []
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
language = 'en'
exclude_patterns = []
pygments_style = None
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
htmlhelp_basename = 'microhildoc'
latex_elements = {}
latex_documents = [(
    master_doc, 'microhil.tex', u'microhil Documentation',
    u'Vladimir Roncevic \\textless{}elektron.ronca@gmail.com\\textgreater{}',
    'manual'
)]
man_pages = [(master_doc, 'microhil', u'microhil Documentation', [author], 1)]
texinfo_documents = [(
    master_doc, 'microhil', u'microhil Documentation', author, 'microhil',
    'One line description of project.', 'Miscellaneous'
)]
epub_title = project
epub_exclude_files = ['search.html']
