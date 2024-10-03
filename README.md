IoT Dehumidifier - Arduino R4 WiFi Uno
======================================

Project Overview
----------------

This project is a school assignment focused on building a smart dehumidifier system using an Arduino R4 WiFi Uno. The Arduino device reads humidity levels and displays the status on an LED matrix, sending notifications via email if the humidity crosses a certain threshold.

**Please note:** All references to controlling the dehumidifier are part of version 2, which is coming soon. In the current version, only notifications are sent, and no actual control over a physical dehumidifier is implemented.

Features
--------

-   **Real-time Humidity Monitoring:** Humidity is measured using a sensor and displayed on an LED matrix in real-time.
-   **Email Notifications:** When the humidity level exceeds 55%, an email notification is sent, reminding the user to turn on the dehumidifier.
-   **Client Dashboard:** Daily statistics, including humidity levels and current electricity prices in the area, can be viewed on the client interface.

Client and Server
-----------------

-   **Client:** Developed using React and TypeScript, the client interface shows daily statistics and electricity prices. It can be accessed [here](https://github.com/D-Hankin/iotDehumidifierClient).
-   **Server:** The server-side logic handles database operations and communication with the client. It can be accessed [here](https://github.com/D-Hankin/iotDehumidifierServer).

Hardware
--------

-   **Arduino R4 WiFi Uno**
-   **Humidity Sensor**
-   **KY-011 & KY-034 LED Modules**
-   **WiFi Module**

How It Works
------------

1.  **Sensor Readings:** The humidity sensor continuously reads the environment's humidity levels.
2.  **LED Display:** The current humidity level is displayed on the built-in LED matrix.
3.  **Email Notification:** If the humidity level exceeds 55%, an email is sent using the integrated JavaMailSender service.
4.  **Client View:** Data is sent to the server and displayed on the client interface, where users can check humidity statistics and electricity prices.


### App Flow
------------

1.  **Arduino → Server:**

    -   The Arduino collects environmental data (e.g., humidity levels) from connected sensors.
    -   This data is transmitted to the server via HTTP requests, using the Arduino's Wi-Fi connection.
      
2.  **Server → MongoDB:**

    -   Upon receiving the data, the server processes and stores it in a MongoDB database.
    -   MongoDB ensures the data is stored in a structured format, enabling easy retrieval for future use.
      
3.  **Server → Notification Mail:**

    -   If the Arduino reports a humidity level above 55%, the server sends a notification email to the logged-in user's email address.
    -   The notification is triggered only once when the condition is met, to avoid repetitive emails.
      
4.  **MongoDB → Server:**

    -   The server queries MongoDB to retrieve historical data or the latest statistics as needed.
    -   This data is used for further processing or for serving the client application.
      
5.  **Server → Client:**

    -   The client (built with React and TypeScript) sends requests to the server to retrieve updated information, such as daily statistics or current electricity prices.
    -   The server responds with the requested data, which is then displayed in the client interface for the user.


Installation and Setup
----------------------

1.  Clone the repository to your local machine.
2.  Set up the Arduino environment with the necessary libraries.
3.  Create a 'settings.h' file where you will need to store your machine ip address along with your wifi login credentials.
4.  Modify the `application.properties` file on the server to include your email and MongoDB configuration.

Future Enhancements (Version 2)
-------------------------------

-   Full control of the dehumidifier based on real-time sensor data.
