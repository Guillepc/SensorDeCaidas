📡 Detector de Caídas con Arduino MKR WAN 1310 y LoRaWAN
Este proyecto consiste en el desarrollo de un sistema IoT portátil para la detección de caídas en personas mayores, utilizando un Arduino MKR WAN 1310, un sensor MPU6050, un módulo GPS NEO-6M y conectividad LoRaWAN a través de The Things Network (TTN).

El sistema detecta caídas mediante un algoritmo basado en aceleración y orientación, obtiene la ubicación del evento y envía una alerta con la posición a través de LoRaWAN. También incluye funcionalidades de bajo consumo para optimizar la duración de la batería.

📁 Estructura del repositorio
Archivo	Descripción
SensorDeCaidas.ino	Código principal del proyecto. Implementa el algoritmo de detección de caídas, obtiene ubicación por GPS y envía alertas mediante LoRa.
AlgoritmoCaidas.ino	Implementación específica del algoritmo de detección de caídas utilizando datos del acelerómetro y giroscopio.
PruebaAcelerometro.ino	Script de prueba para leer y visualizar datos del sensor MPU6050 (aceleración y giro).
PruebaGps.ino	Código de prueba para comprobar la lectura de datos GPS desde el módulo NEO-6M.
PruebaLORA.ino	Código de prueba para verificar la conexión y envío de mensajes mediante LoRaWAN.
CreacionGraficasAceleracion	Script para representar gráficamente los datos de aceleración recogidos, útil para ajustar y validar el algoritmo de detección.

🔧 Tecnologías y componentes
Arduino MKR WAN 1310

Sensor MPU6050 (acelerómetro y giroscopio)

Módulo GPS NEO-6M

The Things Network (TTN)

Plataforma de visualización de datos y correo vía webhook

📬 Funcionalidad destacada
Detección de caídas clasificadas por tipo

Obtención de ubicación al detectar una caída

Envío de alerta vía LoRaWAN a TTN

Notificación automática por correo electrónico (vía webhook)

Modo de bajo consumo entre envíos para prolongar batería

📌 Estado del proyecto
✅ Funcionalidad de detección implementada
✅ Comunicación con TTN verificada
✅ Envío de alertas con localización funcional
⏳ Posible mejora futura con IA y miniaturización

🧠 Autor
Este proyecto ha sido desarrollado como parte de un Trabajo de Fin de Grado en Ingeniería de Tecnologías y Servicios de Telecomunicación.

