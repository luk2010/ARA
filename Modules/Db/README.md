# ARA Database Module

The ARA Database Module defines a set of interfaces used to communicate with
a local or an online database.

The module defines a DbConnectionPlugin that is used to load a DbConnection
from a `ARA::Plugin` interface.

## Model structure

The database module defines a `DbModel` class one can subclass to make the basic
CRUD functions available for a structure. You have to define each CRUD functions
in the model class.

## Connection and requests

You create `DbRequest` objects directly by giving a valid `DbConnection` object. Then,
you fill your request depending on the request type (see `DbRequestType`) and you
execute it with `DbConnection::execute`.
