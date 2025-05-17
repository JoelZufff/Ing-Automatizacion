using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graphic_interface
{

    public partial class TCP_connection : Form
    {
        private TcpClient client;
        static NetworkStream stream;

        // Para medir el tiempo desde la presion de start
        private DateTime startTime;

        public TCP_connection()
        {
            InitializeComponent();
            this.MaximizeBox = false;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;

            Show_Connection_Panel();
        }

        private void Show_Connection_Panel()
        {
            // Ocultamos todos los paneles que esten abiertos
            Panel_Graph.Visible = false;

            // Mostramos el panel con tamaño
            this.Size = new Size(270, 175);

            // Centrar ventana en la pantalla
            this.Location = new Point
            (
                (Screen.PrimaryScreen.WorkingArea.Width - this.Width) / 2,
                (Screen.PrimaryScreen.WorkingArea.Height - this.Height) / 2
            );

            Panel_Connection.Visible = true;
        }

        private void Show_Graph_Panel()
        {
            // Ocultamos todos los paneles que esten abiertos
            Panel_Connection.Visible = false;

            // Mostramos el panel con tamaño
            this.Size = new Size(800, 900);

            // Centrar ventana en la pantalla
            this.Location = new Point
            (
                (Screen.PrimaryScreen.WorkingArea.Width - this.Width) / 2,
                (Screen.PrimaryScreen.WorkingArea.Height - this.Height) / 2
            );

            Panel_Graph.Visible = true;
        }

        private async void Button_Connect_Click(object sender, EventArgs e)
        {
            // Conectar con servidor TCP, y si se conectar, ocultar pantalla y mostrar graficos
            try
            {
                client = new TcpClient();
                
                // Intento de conexion con timeout de 5 s
                var connectTask = client.ConnectAsync(Textbox_IP.Text, int.Parse(Textbox_Port.Text));
                if (await Task.WhenAny(connectTask, Task.Delay(5000)) != connectTask)
                    throw new TimeoutException("Tiempo de conexión agotado");

                stream = client.GetStream();

                // Iniciar recepción de datos en segundo plano
                _ = Task.Run(() => dataReception());

                // Mostramos panel de graficacion
                Show_Graph_Panel();
            }
            catch (SocketException sex)
            {
                MessageBox.Show($"Error de conexión: {sex.SocketErrorCode}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (TimeoutException tex)
            {
                MessageBox.Show(tex.Message, "Timeout", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error inesperado: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                if (client?.Connected == false)
                    client?.Dispose();
            }
        }

        private void processData(string receivedData)
        {
            
        }

        private async Task dataReception()
        {
            try
            {
                while (client.Connected)
                {
                    byte[] data = new byte[32];
                    int totalRead = 0;

                    while (totalRead < 32)
                    {
                        int bytesRead = await stream.ReadAsync(data, totalRead, 32 - totalRead);
                        if (bytesRead == 0)
                            break; // conexión cerrada o error

                        totalRead += bytesRead;
                    }

                    if (totalRead == 32)        // Se leyeron los 32 bytes
                    {
                        // Almacenar los datos en un archivo, graficar en tiempo real ciertos datos 

                        // Almacenamos el tiempo para graficar
                        TimeSpan elapsed = DateTime.Now - startTime;
                        double seconds = elapsed.TotalSeconds;

                        string path = "Muestreo.txt"; // Puedes poner ruta completa si quieres

                        // Abre el archivo para agregar (append), si no existe se crea
                        using (StreamWriter sw = new StreamWriter(path, true))
                            sw.WriteLine(BitConverter.ToSingle(data, 24).ToString("F4"));    // Guarda con 4 decimales (opcional)
                        /*
                        // Agregar punto con X = tiempo transcurrido en segundos
                        Chart_Vel.Series["v_d"].Points.AddXY(seconds, BitConverter.ToSingle(data, 0));
                        //Chart_Vel.Series["v"].Points.AddXY(seconds, BitConverter.ToSingle(data, 1));

                        // Refrescar el gráfico si es necesario
                        Chart_Vel.Invalidate();
                        */
                    }
                    else
                    {
                        MessageBox.Show("No se recibieron los bytes completos", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break; // o manejar reconexión, etc.
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error en recepción de datos: " + ex.Message);
            }
        }

        private async void Button_Start_Click(object sender, EventArgs e)
        {
            if (client != null && client.Connected && stream != null)
            {
                List<byte> buffer = new List<byte>();

                // Byte de inicio del mensaje
                buffer.Add(0xAA);

                // Empaquetamos valores de ganancias
                buffer.AddRange(BitConverter.GetBytes((float)UD_k1.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_k2.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_k3.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_k4.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_kp.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_kv.Value));

                // Empaquetamos valores de configuracion
                buffer.AddRange(BitConverter.GetBytes((float)UD_Time.Value));
                buffer.AddRange(BitConverter.GetBytes((float)UD_Vel.Value));

                // Enviar todos los bytes por el stream
                await stream.WriteAsync(buffer.ToArray(), 0, buffer.Count);

                startTime = DateTime.Now;       // Guardar el momento de inicio
            }
            else
            {
                MessageBox.Show("No hay conexión con el servidor", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
