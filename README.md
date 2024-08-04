# Telemetría 5G para Euskelec

Este repositorio contiene el proyecto de telemetría 5G desarrollado desde cero por Luis Moricz para el equipo Euskelec. Utiliza un ESP8266 como microcontrolador principal, junto con diversos sensores y componentes para el monitoreo y control de un sistema de powertrain en vehículos eléctricos de competición.

## Componentes del Sistema

### Hardware

- **ESP8266**: Microcontrolador basado en WiFi, encargado de la recolección y transmisión de datos.
- **Sensor DHT22**: Sensor digital de temperatura y humedad, utilizado para monitorear las condiciones ambientales dentro del compartimiento del powertrain.
- **MPU6050**: Sensor que combina acelerómetro y giroscopio, utilizado para medir el ángulo y la velocidad del giro del volante.
- **Pantalla ILI9341**: Pantalla TFT de 2.8 pulgadas, utilizada para mostrar información en tiempo real al piloto. Ofrece menús que visualizan datos como temperatura del motor, temperatura del compartimento del powertrain, revoluciones del motor eléctrico, trazado del circuito, tiempos (mejor vuelta, última vuelta, diferencia con otros pilotos), velocidad, posición de carrera, estado del botón de radio y luces de posición.
- **Router 5G**: Dispositivo de red que proporciona conectividad 5G mediante una SIM, permitiendo la transmisión de datos en una red privada.
- **Intercomunicador VOIP**: Sistema de comunicación integrado en el casco del piloto para permitir la comunicación en tiempo real con el equipo de soporte.
- **Zócalo de Conexión Especial**: Utilizado para la conexión del ESP8266, proporcionando una conexión robusta y fiable.
- **Conectores Cannon Macho-Hembra**: Conectores utilizados para toda la sensórica, garantizando conexiones seguras y resistentes.
- **Malla Protectora y Tubo Corrugado**: Protegen los cables de conexión, añadiendo durabilidad y resistencia a las condiciones del entorno.
- **Piezas en 3D**: Piezas impresas en 3D diseñadas para montar la pantalla ILI9341 y el soporte de la cámara en el monoplaza.
- **Conexión UARTCAN a USB**: Conexión para extraer información completa de la centralita del monoplaza (EMU).
- **GPS NEO6M**: Módulo GPS utilizado para obtener datos precisos de velocidad, trazado del circuito y posiciones relativas a otros pilotos.

### Software

- **Mosquitto MQTT**: Broker MQTT de código abierto utilizado para la transmisión de datos entre el ESP8266 y el servidor.
- **Grafana**: Herramienta de análisis y visualización de datos, utilizada para crear un dashboard personalizado donde se visualizan los datos de telemetría en tiempo real.

## Descripción del Proyecto

### Arquitectura del Sistema

- **Recolección de Datos**:
  - **Temperatura y Humedad**: El sensor DHT22 mide la temperatura y la humedad dentro del compartimiento del powertrain.
  - **Giro del Volante**: El sensor MPU6050 mide el ángulo y la velocidad del giro del volante.
  - **Velocidad y Posición**: El módulo GPS NEO6M obtiene datos de velocidad, trazado, y posiciones relativas a otros pilotos.

- **Procesamiento y Visualización Local**:
  - **Pantalla ILI9341**: Muestra datos en tiempo real como temperatura del motor, revoluciones, tiempos de vuelta, posición de carrera, velocidad, estado del botón de radio y luces de posición.

- **Transmisión de Datos**:
  - **Router 5G**: Transmite datos en tiempo real a través de una red 5G privada.
  - **Mosquitto MQTT**: El ESP8266 envía los datos al broker MQTT Mosquitto.

- **Visualización Remota**:
  - **Dashboard en Grafana**: Procesa y visualiza los datos en un dashboard personalizado, permitiendo al equipo de soporte monitorear el rendimiento del vehículo en tiempo real.

- **Comunicación en Tiempo Real**:
  - **Intercomunicador VOIP**: Permite la comunicación en tiempo real con el equipo de soporte.

### Conexiones y Protección

- **Zócalo de Conexión Especial**: Garantiza una conexión segura y robusta hacia el ESP8266.
- **Conectores Cannon Macho-Hembra**: Conexiones seguras y resistentes a las vibraciones.
- **Malla Protectora y Tubo Corrugado**: Protegen los cables de conexión, previniendo daños por abrasión.

### Piezas en 3D

- **Montaje de la Pantalla ILI9341**: Piezas impresas en 3D para montar la pantalla.
- **Soporte de la Cámara**: Soportes impresos en 3D para montar la cámara en el monoplaza.

### Conexión UARTCAN a USB

Se ha implementado una conexión UARTCAN a USB para extraer información completa de la centralita del monoplaza (EMU).

### PMU

Hemos creado la Unidad de Potencia y Gestión (PMU) que integra todos los componentes y sistemas, proporcionando una solución completa y optimizada para el control y monitoreo del powertrain.

### Código Base

Desarrollado desde cero por Luis Moricz, incluye:
- **Lectura de Sensores**: Rutinas para leer datos de los sensores DHT22 y MPU6050.
- **Interfaz de Usuario**: Código para la visualización de datos en la pantalla ILI9341.
- **Comunicación MQTT**: Implementación del protocolo MQTT.
- **Integración con Grafana**: Scripts para enviar datos al servidor de Grafana.

## Instalación y Configuración

### Requisitos

- ESP8266 con entorno de desarrollo Arduino IDE.
- Sensor DHT22.
- MPU6050.
- Pantalla ILI9341.
- Router 5G con SIM activa.
- GPS NEO6M.
- Servidor para Mosquitto MQTT y Grafana.
- Casco con Intercomunicador VOIP.

### Pasos de Instalación

1. **Clonar el Repositorio**:
   ```bash
   git clone https://github.com/usuario/telemetria-5G-euskelec.git
2. **Configurar el Entorno de Desarrollo:**
   
- Instalar Arduino IDE.
- Añadir la URL del gestor de placas ESP8266: http://arduino.esp8266.com/stable/package_esp8266com_index.json.
- Instalar las bibliotecas necesarias.

3. **Configurar el Router 5G:**
   
- Insertar la SIM y asegurar la conexión 5G.

4. **Configurar Mosquitto y Grafana:**
   
- Instalar y configurar Mosquitto y Grafana en el servidor.
  
5. **Cargar el Código en el ESP8266:**
   
- Conectar el ESP8266 al ordenador y cargar el código.

6. **Configurar el Intercomunicador VOIP:**
   
- Instalar y configurar el intercomunicador en el casco del piloto.

### Agradecimientos
Queremos expresar nuestro más sincero agradecimiento al Centro de Formación Somorrostro y a todos los integrantes del equipo Somoracers 2024 por su apoyo y dedicación.

### Prohibición de Distribución
La redistribución o resubida de este repositorio a cualquier otra plataforma o canal está estrictamente prohibida sin la autorización previa del autor.
