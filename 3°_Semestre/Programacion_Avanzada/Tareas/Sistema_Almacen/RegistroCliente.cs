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
    public partial class RegistroCliente : Form
    {
        public RegistroCliente()
        {
            InitializeComponent();
        }

        private void Registro_Load(object sender, EventArgs e) {}

        private void RegExp_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= 32 && e.KeyChar <= 47) || (e.KeyChar >= 58))
                e.Handled = true;
        }

        private void RegTel_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= 32 && e.KeyChar <= 47) || (e.KeyChar >= 58))
                e.Handled = true;
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= 33 && e.KeyChar <= 64) || (e.KeyChar >= 91 && e.KeyChar <= 96) || (e.KeyChar >= 123))
                e.Handled = true;
        }


        private void Registrar_Click(object sender, EventArgs e)
        {
            // Validacion de datos

            if ((RegExp.Text.Length < 6) ||  (RegName.Text.Length == 0) ||  (RegTel.Text.Length < 10) ||  (RegCarr.SelectedIndex < 0) ||  (RegStatus.SelectedIndex < 0))
            {
                MessageBox.Show("Ingrese los datos completos","Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            foreach (var Cliente in Variables.Lista_Clientes)
                if (RegExp.Text.Contains(Cliente.expediente))
                {
                    MessageBox.Show("El expediente ingresado ya existe", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

            // Si se paso la validacion de datos, realizamos el registro y confirmamos

            cliente Aux = new cliente(RegName.Text, RegExp.Text, RegTel.Text, RegCarr.Text, RegStatus.Text);
            Variables.Lista_Clientes.Add(Aux);

            if (Variables.Lista_Clientes.Contains(Aux))
                MessageBox.Show("Registro Existoso","Exito",MessageBoxButtons.OK, MessageBoxIcon.Information);
            else
                MessageBox.Show("Registro Fallido", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

            this.Close();
        }
    }
}