## Решение на 8 баллов
### Команды для запуска:
Первый терминал:

```
./solve.o
```
Второцй терминал:
```
./reader.o input_path output_path
```
## Алгоритм
1. После запуска, процесс reader производит чтение данных из файла, а затем попадает в режим ожидания создания fifo канала
```
while ((rtosfd = open(rtosfifo, O_WRONLY)) == -1)
    {
        fprintf(stdout, "Процесс чтения ожидает создания канала\n");
        sleep(5);
    }
```
2. Тем временем процесс solve создает два канала, один для передачи данных во время чтения, второй во время записи
3. После создания канала, процесс reader производит запись данных в первый канал
4. Процесс solve ожидает появления данных в канале, затем производит решение посталенной задачи и производит запись данных во второй канал
5. Процесс reader ожидает появления данных во втором канале, а затем производит запись данных в файл
    
