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

### Contribuciones
Las contribuciones al proyecto son bienvenidas. Si deseas contribuir, por favor sigue estos pasos:
1. Haz un fork del repositorio.
2. Crea una nueva rama para tu característica o corrección de errores.
3. Realiza tus cambios y haz commit de ellos.
4. Envía un pull request describiendo tus cambios y por qué deberían ser fusionados.