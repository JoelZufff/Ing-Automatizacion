using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sistema_Almacen
{   
    public partial class AdminLogin : Form
    {
        public AdminLogin()
        {
            InitializeComponent();
        }

        private void Administrador_Load(object sender, EventArgs e) {}

        private void SendButton_Click(object sender, EventArgs e)
        {
            if (TextBoxPswd.Text == Variables.Admin_Password) // Ingreso la contraseña bien
            {
                // Abrir ventana de administrador
                Admin Admin_Window = new Admin();
                Admin_Window.FormClosed += Window_FormClosed; // Enlazamos funcion con evento de cierre

                Admin_Window.Show();
                this.Hide();
            }
            else
            {
                MessageBox.Show("Clave Incorrecta", "Error de Acceso", MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.Close();
            }

        }

        private void Window_FormClosed(object sender, FormClosedEventArgs e) { this.Close(); }

        private void TextBoxPswd_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
                SendButton.PerformClick();
        }
    }
}
