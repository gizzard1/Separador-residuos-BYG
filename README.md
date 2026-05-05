# Sistema de Gestión de Residuos para ESP32 BYG

### Descripción del proyecto
El proyecto es un sistema adaptado para un ESP32 que permite a los usuarios depositar residuos en un contenedor específico. El sistema incluye una interfaz web para que los usuarios puedan registrarse, iniciar sesión y realizar depósitos. Además, el sistema calcula un bono basado en el tipo de residuo depositado y lo asocia al usuario.

### Estructura del proyecto
- **app/Models**: Contiene los modelos de Eloquent para `User`, `Container` y `Deposit`.
- **database/migrations**: Contiene las migraciones para crear las tablas `users`, `containers` y `deposits`.
- **routes/web.php**: Define las rutas para la aplicación web.
- **resources/views**: Contiene las vistas Blade para la interfaz de usuario.

### Funcionalidades principales
1. **Registro de usuarios**: Los usuarios pueden registrarse proporcionando su nombre, correo electrónico, contraseña y código de estudiante.
2. **Inicio de sesión**: Los usuarios pueden iniciar sesión para acceder a sus cuentas.
3. **Depósito de residuos**: Los usuarios pueden seleccionar un contenedor, ingresar el tipo de residuo y realizar un depósito. El sistema calculará un bono basado en el tipo de residuo y lo asociará al usuario.
4. **Gestión de contenedores**: El sistema permite la creación y gestión de contenedores, cada uno con una contraseña para asegurar su acceso.

### Tecnologías utilizadas
- **Laravel**: Framework PHP para el desarrollo de la aplicación web.
- **Eloquent ORM**: Para la gestión de la base de datos y las relaciones entre los modelos.
- **Blade**: Motor de plantillas para las vistas.
- **MySQL**: Base de datos para almacenar la información de usuarios, contenedores y depósitos.
- **Embebido en ESP32**: El sistema está diseñado para ser ejecutado en un ESP32, lo que permite su integración con hardware para la gestión de los contenedores de residuos.

### Instrucciones para la instalación
1. Clonar el repositorio en tu máquina local.
2. Configurar la base de datos en el archivo `.env`.
3. Ejecutar las migraciones para crear las tablas necesarias:
```bash
    php artisan migrate
```
4. Iniciar el servidor de desarrollo:
```bash
    php artisan serve
```
5. Acceder a la aplicación a través de `http://localhost:8000` en tu navegador web.

### Instrucciones para instalar en ESP32
1. Asegúrate de tener el entorno de desarrollo para ESP32 configurado (Arduino IDE o PlatformIO).
2. Compila y sube el código del ESP32 que se encuentra en la raíz del proyecto.
3. Reemplaza las credenciales de Wi-Fi en el código del ESP32 con las de tu red.
4. El ESP32 se conectará a la red Wi-Fi y podrá interactuar con la aplicación web o puedes probar con Postman.
    4.1 Para probar con Postman, monitorea el puerto serie del ESP32 para obtener la dirección IP asignada.
    4.2 Envía una solicitud WebSocket a la dirección "ws://<IP_DEL_ESP32>:81" para interactuar con el sistema.
    4.3 Envía un mensaje con la estructura "PASSWORD:COMANDO" para encender el led deseado.

### Tabla de listado de comandos para el ESP32
PASSWORD:21 -> Enciende el led verde
PASWORD:41 -> Enciende el led azul
PASSWORD:51 -> Enciende el led blanco
PASSWORD:181 -> Enciende el led rojo
PASSWPORD:180 -> Apaga el led rojo
PASSWORD:P1 -> Enciende el led amarillo (Simulación de una puerta abierta)
PASSWORD:P0 -> Apaga el led amarillo (Simulación de una puerta cerrada, en este estado no es posible encender otro led que no sea el rojo)

### Contribuciones
Las contribuciones al proyecto son bienvenidas. Si deseas contribuir, por favor sigue estos pasos:
1. Haz un fork del repositorio.
2. Crea una nueva rama para tu característica o corrección de errores.
3. Realiza tus cambios y haz commit de ellos.
4. Envía un pull request describiendo tus cambios y por qué deberían ser fusionados.