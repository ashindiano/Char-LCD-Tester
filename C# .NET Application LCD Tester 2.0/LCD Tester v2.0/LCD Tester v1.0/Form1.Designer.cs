namespace LCD_Tester_v1._0
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.Connect_button = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.mode4_button = new System.Windows.Forms.Button();
            this.Auto_off_button = new System.Windows.Forms.Button();
            this.Auto_on_button = new System.Windows.Forms.Button();
            this.lcd_1_button = new System.Windows.Forms.Button();
            this.Lcd_2_button = new System.Windows.Forms.Button();
            this.mode8_button = new System.Windows.Forms.Button();
            this.clear_button = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.status = new System.Windows.Forms.ToolStripStatusLabel();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.time_date = new System.Windows.Forms.Button();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(60, 27);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(253, 21);
            this.comboBox1.TabIndex = 0;
            // 
            // Connect_button
            // 
            this.Connect_button.Location = new System.Drawing.Point(202, 68);
            this.Connect_button.Name = "Connect_button";
            this.Connect_button.Size = new System.Drawing.Size(111, 26);
            this.Connect_button.TabIndex = 1;
            this.Connect_button.Text = "Connect";
            this.Connect_button.UseVisualStyleBackColor = true;
            this.Connect_button.Click += new System.EventHandler(this.Connect_button_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(368, 27);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(254, 20);
            this.textBox1.TabIndex = 2;
            // 
            // richTextBox1
            // 
            this.richTextBox1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.richTextBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.richTextBox1.Location = new System.Drawing.Point(16, 237);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(643, 221);
            this.richTextBox1.TabIndex = 3;
            this.richTextBox1.Text = "";
            this.richTextBox1.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // mode4_button
            // 
            this.mode4_button.Location = new System.Drawing.Point(60, 132);
            this.mode4_button.Name = "mode4_button";
            this.mode4_button.Size = new System.Drawing.Size(111, 26);
            this.mode4_button.TabIndex = 4;
            this.mode4_button.Text = "4 BIT Mode ON";
            this.mode4_button.UseVisualStyleBackColor = true;
            this.mode4_button.Click += new System.EventHandler(this.mode4_button_Click);
            // 
            // Auto_off_button
            // 
            this.Auto_off_button.Location = new System.Drawing.Point(511, 132);
            this.Auto_off_button.Name = "Auto_off_button";
            this.Auto_off_button.Size = new System.Drawing.Size(111, 26);
            this.Auto_off_button.TabIndex = 5;
            this.Auto_off_button.Text = "Auto Swap OFF";
            this.Auto_off_button.UseVisualStyleBackColor = true;
            this.Auto_off_button.Click += new System.EventHandler(this.Auto_off_button_Click);
            // 
            // Auto_on_button
            // 
            this.Auto_on_button.Location = new System.Drawing.Point(368, 132);
            this.Auto_on_button.Name = "Auto_on_button";
            this.Auto_on_button.Size = new System.Drawing.Size(111, 26);
            this.Auto_on_button.TabIndex = 6;
            this.Auto_on_button.Text = "Auto Swap ON";
            this.Auto_on_button.UseVisualStyleBackColor = true;
            this.Auto_on_button.Click += new System.EventHandler(this.Auto_on_button_Click);
            // 
            // lcd_1_button
            // 
            this.lcd_1_button.Location = new System.Drawing.Point(368, 68);
            this.lcd_1_button.Name = "lcd_1_button";
            this.lcd_1_button.Size = new System.Drawing.Size(111, 26);
            this.lcd_1_button.TabIndex = 7;
            this.lcd_1_button.Text = "LCD 1st Line";
            this.lcd_1_button.UseVisualStyleBackColor = true;
            this.lcd_1_button.Click += new System.EventHandler(this.lcd_1_button_Click);
            // 
            // Lcd_2_button
            // 
            this.Lcd_2_button.Location = new System.Drawing.Point(511, 68);
            this.Lcd_2_button.Name = "Lcd_2_button";
            this.Lcd_2_button.Size = new System.Drawing.Size(111, 26);
            this.Lcd_2_button.TabIndex = 8;
            this.Lcd_2_button.Text = "LCD 2nd Line";
            this.Lcd_2_button.UseVisualStyleBackColor = true;
            this.Lcd_2_button.Click += new System.EventHandler(this.lcd_2_button_Click);
            // 
            // mode8_button
            // 
            this.mode8_button.Location = new System.Drawing.Point(202, 132);
            this.mode8_button.Name = "mode8_button";
            this.mode8_button.Size = new System.Drawing.Size(111, 26);
            this.mode8_button.TabIndex = 9;
            this.mode8_button.Text = "8 BIT Mode ON";
            this.mode8_button.UseVisualStyleBackColor = true;
            this.mode8_button.Click += new System.EventHandler(this.mode8_button_Click);
            // 
            // clear_button
            // 
            this.clear_button.Location = new System.Drawing.Point(548, 469);
            this.clear_button.Name = "clear_button";
            this.clear_button.Size = new System.Drawing.Size(111, 26);
            this.clear_button.TabIndex = 11;
            this.clear_button.Text = "Clear";
            this.clear_button.UseVisualStyleBackColor = true;
            this.clear_button.Click += new System.EventHandler(this.clear_button_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.BackColor = System.Drawing.Color.Transparent;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.status});
            this.statusStrip1.Location = new System.Drawing.Point(0, 501);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(680, 22);
            this.statusStrip1.TabIndex = 12;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // status
            // 
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(79, 17);
            this.status.Text = "Disconnected";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(60, 68);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(111, 26);
            this.button2.TabIndex = 18;
            this.button2.Text = "Refresh Ports";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(287, 476);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(121, 13);
            this.label1.TabIndex = 19;
            this.label1.Text = "www.vidnis.blospot.com";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(368, 179);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(111, 34);
            this.button1.TabIndex = 20;
            this.button1.Text = "Update Date and Time";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // time_date
            // 
            this.time_date.Location = new System.Drawing.Point(511, 179);
            this.time_date.Name = "time_date";
            this.time_date.Size = new System.Drawing.Size(111, 34);
            this.time_date.TabIndex = 21;
            this.time_date.Text = "Enquire Date and Time";
            this.time_date.UseVisualStyleBackColor = true;
            this.time_date.Click += new System.EventHandler(this.time_date_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(680, 523);
            this.Controls.Add(this.time_date);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.clear_button);
            this.Controls.Add(this.mode8_button);
            this.Controls.Add(this.Lcd_2_button);
            this.Controls.Add(this.lcd_1_button);
            this.Controls.Add(this.Auto_on_button);
            this.Controls.Add(this.Auto_off_button);
            this.Controls.Add(this.mode4_button);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.Connect_button);
            this.Controls.Add(this.comboBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "16x2 LCD Tester v2.0          Author : Ash Indiano";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button Connect_button;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button mode4_button;
        private System.Windows.Forms.Button Auto_off_button;
        private System.Windows.Forms.Button Auto_on_button;
        private System.Windows.Forms.Button lcd_1_button;
        private System.Windows.Forms.Button Lcd_2_button;
        private System.Windows.Forms.Button mode8_button;
        private System.Windows.Forms.Button clear_button;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel status;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button time_date;
    }
}

