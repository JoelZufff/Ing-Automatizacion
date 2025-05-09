using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;


namespace Graphic_interface
{
    internal class Program
    {
        private static TcpClient client;
        private static NetworkStream stream;
        private static byte[] data;
        private static string receivedData = "";

        static void Main(string[] args)
        {
            // Dirección IP y puerto del servidor TCP
            string serverIp     = "127.0.0.1";
            int port            = 12345;

            // Inicializamos la conexión
            client = new TcpClient(serverIp, port);
            stream = client.GetStream();
            data = new byte[256]; // Buffer para recibir datos

            // Empezamos un hilo para recibir datos
            Thread receiveThread = new Thread(new ThreadStart(ReceiveData));
            receiveThread.Start();

            // Esperamos que el usuario presione una tecla para cerrar el programa
            Console.WriteLine("Presiona cualquier tecla para salir...");
            Console.ReadKey();

            // Cerramos la conexión al finalizar
            stream.Close();
            client.Close();
        }

        // Este método es ejecutado en el hilo secundario para recibir los datos
        private static void ReceiveData()
        {
            int bytes;

            while (true)
            {
                try
                {
                    bytes = stream.Read(data, 0, data.Length);
                    if (bytes > 0)
                    {
                        receivedData = Encoding.ASCII.GetString(data, 0, bytes);
                        Console.WriteLine("Datos recibidos: " + receivedData);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error al recibir datos: " + e.Message);
                    break;
                }
            }
        }
    }
}
