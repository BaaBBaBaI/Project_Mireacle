import express from 'express';
import amqplib from 'amqplib';

const app = express();
app.use(express.json());

let channel;

async function setupRabbitMQ() {
  const connection = await amqplib.connect('amqp://localhost');
  channel = await connection.createChannel();

  await channel.assertExchange('dlx_exchange', 'direct', { durable: true });
  await channel.assertQueue('dead_letter_queue', { durable: true });
  await channel.bindQueue('dead_letter_queue', 'dlx_exchange', 'dead');

  await channel.assertQueue('main_queue', {
    durable: true,
    arguments: {
      'x-dead-letter-exchange': 'dlx_exchange',
      'x-dead-letter-routing-key': 'dead',
    }
  });
  console.log('Очереди настроены.');
}

app.post('/tasks', async (req, res) => {
  const payload = req.body;
  const message = JSON.stringify(payload);
  
  channel.sendToQueue('main_queue', Buffer.from(message), { persistent: true });
  console.log('[Producer] Задача отправлена:', payload);
  res.status(202).send({ status: 'Task queued' });
});

setupRabbitMQ().then(() => {
  app.listen(3000, () => console.log('API запущен на порту 3000'));
});