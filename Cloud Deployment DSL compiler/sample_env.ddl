DEPLOYMENT MyApp {
    PROVIDER aws;
    REGION us-east-1;

    SERVICE web {
        IMAGE "nginx:latest";
        CPU 2;
        MEM 1024;
        REPLICAS 2;
        ENV {
            PORT = "8080";
            MODE = "production";
        };
    };

    OPTIMIZE {
        COST 500;
        LATENCY 80;
    };
}
