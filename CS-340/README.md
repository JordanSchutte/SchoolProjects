7-2 README
Jordan Schutte
4/20/2024

Description:
This project involves the creation of a fully functional MongoDB dashboard for Grazioso Salvare. The dashboard allows users to interact with and visualize the Austin Animal Center Outcomes dataset. The main functionalities of the dashboard include:
Interactive options to filter the dataset based on rescue type.
A data table that dynamically responds to filtering options.
Geolocation and pie charts that dynamically respond to filtering options.
Inclusion of the Grazioso Salvare logo and a unique identifier.

Initial state:
<image>

Water rescue:
<image>

Mountain or Wilderness Rescue:
<image>

Disaster or Individual tracking:
<image>

Tools Used:
Python: Programming language used for backend development.
JupyterDash: Python library used for creating web applications in Jupyter notebooks.
Dash: Python framework used for building analytical web applications.
MongoDB: NoSQL database used as the model component for storing and retrieving data.
Pandas: Python library used for data manipulation and analysis.
Plotly: Python library used for interactive data visualization.

Rationale:
MongoDB: MongoDB was chosen as the model component due to its flexibility, scalability, and ease of use with Python. It provides a document-oriented data model, which is well-suited for storing semi-structured data like the Austin Animal Center Outcomes dataset. Additionally, MongoDB's integration with Python through the PyMongo library makes it easy to perform CRUD operations and interact with the database.
Dash: Dash was chosen as the framework for building the web application due to its simplicity, interactivity, and compatibility with Jupyter notebooks. It allows for the creation of interactive and responsive web-based visualizations using familiar Python syntax.

Steps Taken:
Data retrieval from MongoDB using a custom CRUD Python module.
Creation of interactive options (dropdown menu) to filter the dataset.
Development of database queries to match the required filter functionality.
Implementation of a data table that dynamically responds to filtering options.
Creation of geolocation and pie charts that dynamically respond to filtering options.
Testing and deployment of the dashboard to ensure all components work as expected.
Documentation of the project, including the creation of this README file.

Challenges Encountered:
Ensuring proper synchronization between the interactive options and dashboard widgets.
Handling errors and exceptions during data retrieval and processing.
Optimizing the performance of the dashboard for large datasets.
