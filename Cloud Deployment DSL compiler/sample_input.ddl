deployment MyApp {
  provider aws;
  region us-east-1;

  service web {
    image "nginx:latest";
    cpu 2;
    mem 1024;
    replicas 3;
  }

  service webcache {
    image "nginx:latest";
    cpu 2;
    mem 1024;
    replicas 2;
  }

  service db {
    image "mysql:5.7";
    cpu 1;
    mem 2048;
    replicas 1;
  }

  optimize {
    cost 500;
    latency 80;
  }
}
