Telemetría 5G para Euskelec
Este repositorio contiene el proyecto de telemetría 5G desarrollado desde cero por Luis Moricz para el equipo Euskelec, utilizando un ESP8266 como microcontrolador principal, junto con diversos sensores y componentes para el monitoreo y control de un sistema de powertrain en vehículos eléctricos de competición.

Componentes del Sistema
Hardware
ESP8266: Microcontrolador basado en WiFi, encargado de la recolección y transmisión de datos.
Sensor DHT22: Sensor digital de temperatura y humedad, utilizado para monitorear las condiciones ambientales dentro del compartimiento del powertrain.
MPU6050: Sensor que combina acelerómetro y giroscopio, utilizado para medir el ángulo y la velocidad del giro del volante.
Pantalla ILI9341: Pantalla TFT de 2.8 pulgadas, utilizada para mostrar información en tiempo real al piloto.
Router 5G: Dispositivo de red que proporciona conectividad 5G mediante una SIM, permitiendo la transmisión de datos en una red privada.
Intercomunicador VOIP: Sistema de comunicación integrado en el casco del piloto para permitir la comunicación en tiempo real con el equipo de soporte.
Zócalo de Conexión Especial: Utilizado para la conexión del ESP8266, proporcionando una conexión robusta y fiable.
Conectores Cannon Macho-Hembra: Conectores utilizados para toda la sensórica, garantizando conexiones seguras y resistentes.
Malla Protectora y Tubo Corrugado: Utilizados para proteger los cables de conexión, añadiendo una capa adicional de durabilidad y resistencia a las condiciones del entorno.
Piezas en 3D: Piezas impresas en 3D diseñadas para montar la pantalla ILI9341 y el soporte de la cámara en el monoplaza.
Software
Mosquitto MQTT: Broker MQTT de código abierto utilizado para la transmisión de datos entre el ESP8266 y el servidor.
Grafana: Herramienta de análisis y visualización de datos, utilizada para crear un dashboard personalizado donde se visualizan los datos de telemetría en tiempo real.
Descripción del Proyecto
Arquitectura del Sistema
Recolección de Datos:

Temperatura y Humedad: El sensor DHT22 mide la temperatura y la humedad dentro del compartimiento del powertrain. Estos datos son críticos para asegurar que los componentes operen dentro de los rangos seguros y prevenir sobrecalentamientos o condiciones que puedan afectar el rendimiento.
Giro del Volante: El sensor MPU6050 mide el ángulo y la velocidad del giro del volante, proporcionando datos precisos sobre el comportamiento del vehículo y las acciones del piloto.
Procesamiento y Visualización Local:

Pantalla ILI9341: Los datos recolectados se muestran en tiempo real en la pantalla TFT, proporcionando al piloto información crítica como la temperatura, humedad y el ángulo del volante.
Transmisión de Datos:

Router 5G: Los datos son transmitidos en tiempo real a través de una red 5G privada. El router 5G utiliza una SIM para conectarse a la red, asegurando una transmisión rápida y segura.
Mosquitto MQTT: El ESP8266 envía los datos al broker MQTT Mosquitto, que se encarga de gestionar la transmisión de datos entre el dispositivo y el servidor.
Visualización Remota:

Dashboard en Grafana: Los datos son procesados y visualizados en un dashboard personalizado en Grafana. Esto permite al equipo de soporte monitorear el rendimiento del vehículo en tiempo real, analizar datos históricos y recibir alertas sobre cualquier condición crítica.
Comunicación en Tiempo Real:

Intercomunicador VOIP: El sistema incluye un intercomunicador VOIP integrado en el casco del piloto, permitiendo la comunicación en tiempo real con el equipo de soporte para una coordinación efectiva durante la carrera.
Conexiones y Protección
Zócalo de Conexión Especial: La conexión hacia el ESP8266 se ha realizado mediante un zócalo de conexión especial, garantizando una conexión segura y robusta que facilita el mantenimiento y reemplazo del microcontrolador.
Conectores Cannon Macho-Hembra: Toda la sensórica se ha conectado utilizando conectores macho-hembra Cannon, garantizando conexiones seguras y resistentes a las vibraciones y condiciones adversas del entorno de competición.
Malla Protectora y Tubo Corrugado: Los cables de conexión han sido protegidos con malla por encima de un tubo corrugado, añadiendo una capa adicional de durabilidad y resistencia a las condiciones del entorno, previniendo daños por abrasión y mejorando la organización de los cables.
Piezas en 3D
Montaje de la Pantalla ILI9341: Se han diseñado y creado piezas impresas en 3D para montar la pantalla en el vehículo de forma segura y accesible para el piloto.
Soporte de la Cámara: Se han diseñado soportes específicos impresos en 3D para montar la cámara en el monoplaza, asegurando una posición óptima y una sujeción firme.
Código Base
El código base de este proyecto ha sido desarrollado desde cero por Luis Moricz, optimizado para las necesidades específicas del equipo Euskelec. El código incluye:

Lectura de Sensores: Rutinas para leer los datos de los sensores DHT22 y MPU6050.
Interfaz de Usuario: Código para la visualización de datos en la pantalla ILI9341.
Comunicación MQTT: Implementación del protocolo MQTT para la transmisión de datos.
Integración con Grafana: Scripts para enviar datos al servidor de Grafana y configurar el dashboard.
Instalación y Configuración
Requisitos
ESP8266 con entorno de desarrollo Arduino IDE.
Sensor DHT22.
MPU6050.
Pantalla ILI9341.
Router 5G con SIM activa.
Servidor para Mosquitto MQTT y Grafana.
Casco con Intercomunicador VOIP.
Pasos de Instalación
Clonar el Repositorio:

bash
Copiar código
git clone https://github.com/usuario/telemetria-5G-euskelec.git
Configurar el Entorno de Desarrollo:

Instalar Arduino IDE.
Añadir la URL del gestor de placas ESP8266: http://arduino.esp8266.com/stable/package_esp8266com_index.json.
Instalar las bibliotecas necesarias para los sensores (Adafruit DHT, Adafruit MPU6050) y la pantalla (Adafruit ILI9341).
Configurar el Router 5G:

Insertar la SIM en el router y asegurarse de que la conexión 5G esté activa.
Configurar la red privada según las especificaciones del proyecto.
Configurar Mosquitto y Grafana:

Instalar Mosquitto en el servidor y configurar el broker MQTT.
Instalar Grafana y configurar el dashboard para recibir y visualizar los datos de telemetría.
Cargar el Código en el ESP8266:

Conectar el ESP8266 al ordenador y cargar el código desde Arduino IDE.
Realizar las conexiones físicas según el esquema de conexiones proporcionado en el repositorio.
Configurar el Intercomunicador VOIP:

Instalar el intercomunicador en el casco del piloto.
Configurar la comunicación VOIP según las necesidades del equipo.
Contribuciones
Las contribuciones son bienvenidas. Por favor, realiza un fork del repositorio y envía un pull request con tus mejoras.

Licencia
Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo LICENSE para más detalles.

Este proyecto representa una solución avanzada y personalizada para el monitoreo y control de sistemas de powertrain en vehículos de competición, integrando tecnología de vanguardia para asegurar un rendimiento óptimo y seguro.
