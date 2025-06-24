---

# 📡 Detector de Caídas con Arduino MKR WAN 1310 y LoRaWAN

Este proyecto consiste en el desarrollo de un sistema IoT portátil para la **detección de caídas en personas mayores**, utilizando un **Arduino MKR WAN 1310**, un **sensor MPU6050**, un **módulo GPS NEO-6M** y conectividad **LoRaWAN** a través de **The Things Network (TTN)**.

El sistema detecta caídas mediante un algoritmo basado en aceleración y orientación, obtiene la ubicación del evento y envía una alerta con la posición a través de LoRaWAN. También incluye funcionalidades de **bajo consumo energético** para optimizar la duración de la batería.

---

## 📁 Estructura del repositorio

| Archivo                       | Descripción                                                              |
| ----------------------------- | ------------------------------------------------------------------------ |
| `SensorDeCaidas.ino`          | Código principal del proyecto: detección de caídas, GPS y envío LoRa.    |
| `AlgoritmoCaidas.ino`         | Implementación del algoritmo de detección utilizando aceleración y giro. |
| `PruebaAcelerometro.ino`      | Lectura de datos del sensor MPU6050 para pruebas iniciales.              |
| `PruebaGps.ino`               | Lectura y visualización de coordenadas GPS desde el módulo NEO-6M.       |
| `PruebaLORA.ino`              | Pruebas de conexión y envío de paquetes mediante LoRaWAN.                |
| `CreacionGraficasAceleracion` | Script para generar gráficas de aceleración y evaluar el algoritmo.      |

---

## 🔧 Tecnologías y componentes

* ⚙️ **Arduino MKR WAN 1310**
* 📈 **Sensor MPU6050** (acelerómetro y giroscopio)
* 🌐 **Módulo GPS NEO-6M**
* 📡 **LoRaWAN** a través de **The Things Network (TTN)**
* 📬 **Webhook** para notificación por correo electrónico

---

## 📬 Funcionalidad destacada

* ✔️ Detección de caídas clasificadas por tipo
* 🌍 Obtención de coordenadas geográficas tras una caída
* 🚀 Envío de alertas por LoRaWAN a TTN
* 📧 Notificación automática por correo electrónico
* 🔋 Modo de bajo consumo entre transmisiones

---

## 📌 Estado del proyecto

* ✅ Funcionalidad de detección implementada
* ✅ Comunicación y envío a TTN verificados
* ✅ Integración con correo electrónico operativa
* 🔄 Posible mejora futura con IA, miniaturización y nuevas tecnologías de localización

---

## 🧠 Autor

Este proyecto ha sido desarrollado como parte del **Trabajo de Fin de Grado en Ingeniería de Tecnologías y Servicios de Telecomunicación**.

---

¿Quieres que añada una sección opcional para requisitos o cómo cargar los códigos al MKR WAN 1310?
