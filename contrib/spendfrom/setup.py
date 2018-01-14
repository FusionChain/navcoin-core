from distutils.core import setup
setup(name='SOFTspendfrom',
      version='1.0',
      description='Command-line utility for softcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@softcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
